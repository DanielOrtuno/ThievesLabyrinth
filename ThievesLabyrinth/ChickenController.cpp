#include "ChickenController.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "AnimatorComponent.h"
#include "Time.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Level.h"

#include "EnumTypes.h"
#include "Stats.h"
#include "Entity.h"
#include "CapsuleCollider.h"


CChickenController::CChickenController(IEntity* pcOwner) : IEnemyController(pcOwner)
{
	m_nEnemyType = eEnemyType::CHICKEN;
	m_pcTransform = m_pcOwner->GetComponent<CTransform>();
	m_pcRigidbody = m_pcOwner->GetComponent<CRigidbody>();
	m_pcStats = m_pcOwner->GetComponent<CStats>();
	//m_pcAnimator = m_pcOwner->GetComponent<CAnimatorComponent>();
	//m_pcAnimator->SetAnimation(eEnemyAnimation::IDLE);

	m_pcExplosion = (CProjectileEntity*)CEntityManager::CreateEntity(eEntity::PROJECTILE);
	CEntityManager::AddComponentToEntity(m_pcExplosion, eComponent::TRANSFORM);

	CCapsuleCollider* pcAOECollider = (CCapsuleCollider*)CEntityManager::AddComponentToEntity(m_pcExplosion, eComponent::CAPSULE_COLLIDER);
	pcAOECollider->SetHeight(2.0f);
	pcAOECollider->SetRadius(8.0f);
	pcAOECollider->SetTrigger(true);

	CLightComponent* pcAOELight = (CLightComponent*)CEntityManager::AddComponentToEntity(m_pcExplosion, eComponent::LIGHT);

	CProjectileComponent* pcAOEComponent = (CProjectileComponent*)CEntityManager::AddComponentToEntity(m_pcExplosion, eComponent::PROJECTILE_COMPONENT);
	pcAOEComponent->SetDamage(1.0f);
	pcAOEComponent->SetLifeTime(0.01f);
	pcAOEComponent->SetCasterEntity(eEntity::ENVIRONMENT);

	pcAOELight->SetColor({ 1, 0, 0, 1 });
	pcAOELight->SetPosition({ 0, 1, 0 });
	pcAOELight->SetRadius(30.0f);

	m_pcExplosion->SetActiveState(false);
	m_bExploding = false;
	m_tLastPos = CMath::TVECTOR3(0, 0, 0);

	m_fDeathTimer = 0.0f;
}

void CChickenController::Update()
{
	// Make sure you aren't dead
	if (m_pcStats->GetHP() <= 0)
	{
		// You're dead, don't do anything
		m_pcOwner->SetActiveState(false);

		m_pcRigidbody->SetVelocity(CMath::TVECTOR3(0, 0, 0));
		m_pcStats->SetHP(-1);
		// Blow up if you haven't already
		if (!m_bExploding)
		{
			Explode();
		}
		return;
	}
	// Where's the target at?
	m_tLastPos = m_pcOwner->GetComponent<CTransform>()->GetPosition();
	CMath::TVECTOR3 tVectorToTarget = m_pcTarget->GetPosition() - m_tLastPos;
	// Are they close?
	if (CMath::Vector3Magnitude(tVectorToTarget) <= 3.0f)
	{
		// The time has come!
		m_pcOwner->m_pcRoom->m_nEnemyCount--;
		CLevel::UpdateDoors(m_pcOwner->m_pcRoom);
		CLevel::nTotalEnemyCount--;
		Explode();
		m_pcOwner->SetActiveState(false);

		m_pcStats->SetHP(-1);

		m_pcRigidbody->SetVelocity(CMath::TVECTOR3(0, 0, 0));
	}
	else
	{
		// Get to the target!
		CMath::TVECTOR3 tNormalVelocity = CMath::Vector3Normalize(tVectorToTarget);
		CMath::TVECTOR3 tFinalVelocity = (tNormalVelocity * 0.5f) + m_pcRigidbody->GetVelocity();
		float fSpeed = m_pcStats->GetMovementSpeed();
		if (CMath::Vector3Magnitude(tFinalVelocity) > fSpeed)
		{
			tFinalVelocity = CMath::Vector3Normalize(tFinalVelocity) * fSpeed;
		}

		m_pcRigidbody->SetVelocity(tFinalVelocity);
		m_pcTransform->TurnTo(tNormalVelocity);

		/*if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::WALK)
		{
			m_pcAnimator->SetAnimation(eEnemyAnimation::WALK);
			m_pcAnimator->SetAnimationTime(0.0);

		}*/
	}
}

CChickenController& CChickenController::operator=(CChickenController& cCopy)
{
	m_pcTarget = cCopy.m_pcTarget;

	return *this;
}

CChickenController::~CChickenController()
{
	// An explosive chicken leaves nothing behind
	// and nothing to leave behind
	// Blow up if you aren't already
	if (!m_bExploding)
	{
		Explode();
	}
}

void CChickenController::GetPlayerReference()
{
	TEntityMessage message = TEntityMessage(0);
	m_pcTarget = CEventManager::SendEntityMessage(message)->GetComponent<CTransform>();
}

void CChickenController::Explode()
{
	CProjectileEntity* pcNewProjectile = (CProjectileEntity*)CEntityManager::CloneEntity(m_pcExplosion);
	pcNewProjectile->GetComponent<CProjectileComponent>()->SetDamage(m_pcStats->GetBaseDamage());
	pcNewProjectile->m_pcRoom = m_pcOwner->m_pcRoom;
	CTransform* pcProjTransform = pcNewProjectile->GetComponent<CTransform>();

	pcProjTransform->SetPosition(m_tLastPos);

	m_bExploding = true;
	pcNewProjectile->SetActiveState(true);

	CLightComponent* pcProjLight = pcNewProjectile->GetComponent<CLightComponent>();

	if (pcProjLight)
	{
		if (m_pcOwner->m_pcRoom)
		{
			m_pcOwner->m_pcRoom->AddLight(pcProjLight);
		}
	}
}

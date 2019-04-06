#include "MageController.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "AnimatorComponent.h"
#include "Time.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Transform.h"

#include "EnumTypes.h"
#include "Stats.h"
#include "Entity.h"

#include <random>
//#include <vector>

//#include "EventManager.h"
//#include "EnumTypes.h"


CMageController::CMageController(IEntity* pcOwner) : IEnemyController(pcOwner)
{
	m_nEnemyType = eEnemyType::MAGE;

	m_pcOwner = pcOwner;
	m_fSafeDistance = 2.0f;
	m_fDeathTimer = 0.0;

	m_pcTransform = m_pcOwner->GetComponent<CTransform>();
	m_pcRigidbody = m_pcOwner->GetComponent<CRigidbody>();
	m_pcStats = m_pcOwner->GetComponent<CStats>();
	m_pcStats->SetAttackSpeed(1);
	m_pcAnimator = m_pcOwner->GetComponent<CAnimatorComponent>();
	m_pcAnimator->SetAnimation(eEnemyAnimation::IDLE);

	m_fLastAttackTime = 0.0f;

	m_pcProjectileRef = (CProjectileEntity*)CEntityManager::CreateEntity(eEntity::PROJECTILE);
	CEntityManager::AddComponentToEntity(m_pcProjectileRef, eComponent::TRANSFORM);

	CBoxCollider* pcProjCollider = (CBoxCollider*)CEntityManager::AddComponentToEntity(m_pcProjectileRef, eComponent::BOX_COLLIDER);
	pcProjCollider->SetExtent({ 1,1,1 });
	pcProjCollider->SetTrigger(true);

	CEntityManager::AddComponentToEntity(m_pcProjectileRef, eComponent::RIGIDBODY);

	CMeshRenderer* pcMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(m_pcProjectileRef, eComponent::MESH_RENDERER);
	pcMesh->SetVertexBuffer(eVertexBuffer::SPHERE);
	pcMesh->SetIndexBuffer(eIndexBuffer::SPHERE);
	pcMesh->SetTextureCount(1);
	pcMesh->SetTexture(eTexture::ENEMY_MAGE_DIFFUSE, 0);
	pcMesh->SetInputLayout(eInputLayout::DEFAULT);
	pcMesh->SetVertexShader(eVertexShader::DEFAULT);
	pcMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcMesh->SetSampler(eSampler::CLAMP);

	CProjectileComponent* pcProjComponent = (CProjectileComponent*)CEntityManager::AddComponentToEntity(m_pcProjectileRef, eComponent::PROJECTILE_COMPONENT);
	pcProjComponent->SetDamage(10.0f);
	pcProjComponent->SetLifeTime(1.0f);
	pcProjComponent->SetCasterEntity(eEntity::ENEMY);
	m_pcProjectileRef->SetActiveState(false);
}

CMageController::~CMageController()
{
	int debug = 0;
}

void CMageController::GetPlayerReference()
{
	TEntityMessage message = TEntityMessage(0);
	m_pcTarget = CEventManager::SendEntityMessage(message)->GetComponent<CTransform>();
}

void CMageController::Update()
{
	if (m_pcStats->GetHP() <= 0)
	{
		if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::DEATH)
		{
			m_pcAnimator->SetAnimation(eEnemyAnimation::DEATH);
			m_pcAnimator->SetAnimationTime(0.0);
			m_pcAnimator->SetLoop(false);

			m_pcOwner->SetActiveState(false);
			m_pcOwner->GetComponent<CMeshRenderer>()->SetActiveState(true);
			m_pcOwner->GetComponent<CMageController>()->SetActiveState(true);

			m_pcRigidbody->SetVelocity({ 0,0,0 });

			m_pcOwner->GetComponent<CMeshRenderer>()->SetPixelShader(ePixelShader::DISSOLVE);
		}
		else
		{
			m_fDeathTimer += (float)CTime::GetDelta() * 0.25f;
		}


		return;
	}

	m_fLastAttackTime -= (float)CTime::GetDelta();
	


	CMath::TVECTOR3 tVectorToTarget = m_pcTarget->GetPosition() - m_pcTransform->GetPosition();
	if (CMath::Vector3Magnitude(tVectorToTarget) > 15.0f)
	{
		CMath::TVECTOR3 tNormalVelocity = CMath::Vector3Normalize(tVectorToTarget);
		CMath::TVECTOR3 tFinalVelocity = tNormalVelocity * m_pcStats->GetMovementSpeed();

		m_pcTransform->TurnTo(m_pcTarget);
		m_pcRigidbody->SetVelocity(tFinalVelocity);

		if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::WALK)
		{
			m_pcAnimator->SetAnimation(eEnemyAnimation::WALK);
			m_pcAnimator->SetAnimationTime(0.0);			
		}
	}
	else
	{
		m_pcRigidbody->SetVelocity({ 0, 0, 0 });
		m_pcTransform->TurnTo(m_pcTarget);

		if (m_fLastAttackTime <= 0)
		{
			m_pcAnimator->SetAnimation(eEnemyAnimation::ATTACK);
			m_pcAnimator->SetAnimationTime(0.0);
			//m_pcAnimator->SetSpeed(0.5f);
			
			
			m_fLastAttackTime = m_pcStats->GetAttackSpeed();
			m_bIsAttacking = true;
		}

		if (m_bIsAttacking && m_fLastAttackTime < m_pcStats->GetAttackSpeed() -0.35f)
		{
			Attack();
		}

		if (m_fLastAttackTime > 0 && m_fLastAttackTime < .5f)
		{
			if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::IDLE)
			{
				m_pcAnimator->SetAnimation(eEnemyAnimation::IDLE);
				m_pcAnimator->SetAnimationTime(0.0);
				m_pcAnimator->SetSpeed(1.0f);
			}
		}
	}
}

void CMageController::Attack()
{
	int nRand = rand() % (eSFX::FIREBALL2 - eSFX::FIREBALL1 + 1) + eSFX::FIREBALL1;
	CEventManager::SendAudioMessage(TAudioMessage(true, eAudio::SFX, nRand));

	CProjectileEntity* pcNewProjectile = (CProjectileEntity*)CEntityManager::CloneEntity(m_pcProjectileRef);
	pcNewProjectile->m_pcRoom = m_pcOwner->m_pcRoom;

	pcNewProjectile->GetComponent<CProjectileComponent>()->SetDamage(m_pcStats->GetBaseDamage()); //Modify damage based on items/stats/buffs/debuffs

	CTransform* pcProjTransform = pcNewProjectile->GetComponent<CTransform>();
	CTransform* pcOwnerTransform = m_pcOwner->GetComponent<CTransform>();
	CMath::TVECTOR3 tForward(*(CMath::TVECTOR3*)&pcOwnerTransform->GetMatrix().r[2]);

	pcProjTransform->SetPosition(pcOwnerTransform->GetPosition() + tForward * 1.5f + CMath::TVECTOR3{0,3,0});
	pcProjTransform->SetRotation(pcOwnerTransform->GetRotation());

	pcNewProjectile->GetComponent<CRigidbody>()->SetVelocity(CMath::TVECTOR3(tForward) * 30);

	pcNewProjectile->SetActiveState(true);
	m_bIsAttacking = false;
}

CMageController& CMageController::operator=(CMageController & cCopy)
{
	m_pcTarget = cCopy.m_pcTarget;

	return *this;
}

void CMageController::SetTarget(CTransform* pcTarget)
{
	m_pcTarget = pcTarget;
}


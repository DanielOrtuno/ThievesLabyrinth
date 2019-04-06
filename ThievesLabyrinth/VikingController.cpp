#include "VikingController.h"

#include "EventManager.h"
#include "Entity.h"
#include "EnumTypes.h"
#include "Time.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Stats.h"
#include "MeshRenderer.h"
#include "AnimatorComponent.h"
#include "CapsuleCollider.h"
#include "BoxCollider.h"



CVikingController::CVikingController(IEntity* pcOwner) : IEnemyController(pcOwner)
{
	m_nEnemyType = eEnemyType::VIKING;

	m_pcTransform = m_pcOwner->GetComponent<CTransform>();
	m_pcRigidbody = m_pcOwner->GetComponent<CRigidbody>();
	m_pcStats = m_pcOwner->GetComponent<CStats>();
	m_pcStats->SetAttackSpeed(1.0f);
	m_pcAnimator = m_pcOwner->GetComponent<CAnimatorComponent>();

	m_pcAnimator->SetAnimation(eEnemyAnimation::IDLE);

	m_fLastAttackTime = 0.0f;
	m_bIsAttacking = false;

	m_fDeathTimer = 0.0;

	Init();
}

void CVikingController::Update()
{
	if (m_pcStats->GetHP() <= 0)
	{
		if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::DEATH)
		{
			m_pcAnimator->SetAnimation(eEnemyAnimation::DEATH);
			m_pcAnimator->SetAnimationTime(0.0);
			m_pcAnimator->SetSpeed(1.0f);
			m_pcAnimator->SetLoop(false);

			m_pcOwner->SetActiveState(false);
			m_pcOwner->GetComponent<CMeshRenderer>()->SetActiveState(true);
			m_pcOwner->GetComponent<CVikingController>()->SetActiveState(true);

			m_pcRigidbody->SetVelocity({ 0,0,0 });

			m_pcOwner->GetComponent<CMeshRenderer>()->SetPixelShader(ePixelShader::DISSOLVE);
		}
		else
		{
			m_fDeathTimer += (float)CTime::GetDelta() * .25f;
		}

		return;
	}

	m_fLastAttackTime -= (float)CTime::GetDelta();



	CMath::TVECTOR3 tVectorToTarget = m_pcTarget->GetPosition() - m_pcTransform->GetPosition();
	float fDis = m_pcOwner->GetComponent<CCapsuleCollider>()->GetRadius() * m_pcTransform->GetScale().x + 2.0f;
	if (CMath::Vector3Magnitude(tVectorToTarget) > fDis)
	{
		CMath::TVECTOR3 tNormalVelocity = CMath::Vector3Normalize(tVectorToTarget);
		CMath::TVECTOR3 tFinalVelocity = tNormalVelocity * m_pcStats->GetMovementSpeed();

		m_pcTransform->TurnTo(m_pcTarget);
		m_pcRigidbody->SetVelocity(tFinalVelocity);

		// Play Viking walk animation
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
			// Play Viking attack animation
			if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::ATTACK)
			{
				m_pcAnimator->SetAnimation(eEnemyAnimation::ATTACK);
				m_pcAnimator->SetAnimationTime(0.0);
				m_pcAnimator->SetSpeed(1.0f);
			}

			m_bIsAttacking = true;
			m_fLastAttackTime = m_pcStats->GetAttackSpeed();
		}

		if (m_bIsAttacking && m_fLastAttackTime < m_pcStats->GetAttackSpeed() - 0.35f)
		{
			Attack();
		}

		if (!m_bIsAttacking && m_fLastAttackTime <= 0.0f)
		{
			// Player Viking idle animation
			if (m_pcAnimator->GetCurrentAnimation() != eEnemyAnimation::IDLE)
			{
				m_pcAnimator->SetAnimation(eEnemyAnimation::IDLE);
				m_pcAnimator->SetAnimationTime(0.0);
				m_pcAnimator->SetSpeed(1.0f);
			}
		}
	}
}

void CVikingController::Attack()
{
	CProjectileEntity* pcNewProjectile = (CProjectileEntity*)CEntityManager::CloneEntity(m_pcMeleeRef);
	pcNewProjectile->GetComponent<CProjectileComponent>()->SetDamage(m_pcStats->GetBaseDamage()); //Modify damage based on items/stats/buffs/debuffs
	pcNewProjectile->m_pcRoom = m_pcOwner->m_pcRoom;

	CTransform* pcProjTransform = pcNewProjectile->GetComponent<CTransform>();
	CTransform* pcOwnerTransform = m_pcOwner->GetComponent<CTransform>();
	CMath::TVECTOR3 tForward = { *(CMath::TVECTOR3*)&pcOwnerTransform->GetMatrix().r[2] };

	pcProjTransform->SetMatrix(pcOwnerTransform->GetMatrix());
	pcProjTransform->SetPosition(pcOwnerTransform->GetPosition() + CMath::Vector3Normalize(tForward) * 1.5f);

	pcNewProjectile->GetComponent<CRigidbody>()->SetVelocity(tForward * 5.0f);

	pcNewProjectile->SetActiveState(true);
	m_bIsAttacking = false;
}

void CVikingController::Init()
{
	m_pcMeleeRef = (CProjectileEntity*)CEntityManager::CreateEntity(eEntity::PROJECTILE);
	CEntityManager::AddComponentToEntity(m_pcMeleeRef, eComponent::TRANSFORM);

	CBoxCollider* pcMeleeCollider = (CBoxCollider*)CEntityManager::AddComponentToEntity(m_pcMeleeRef, eComponent::BOX_COLLIDER);
	pcMeleeCollider->SetExtent({ 0.33f, 1.0f, 0.33f });
	pcMeleeCollider->SetTrigger(true);

	CEntityManager::AddComponentToEntity(m_pcMeleeRef, eComponent::RIGIDBODY);

	CProjectileComponent* pcMeleeComponent = (CProjectileComponent*)CEntityManager::AddComponentToEntity(m_pcMeleeRef, eComponent::PROJECTILE_COMPONENT);
	pcMeleeComponent->SetDamage(1.0f);
	pcMeleeComponent->SetLifeTime(0.1f);
	pcMeleeComponent->SetCasterEntity(eEntity::ENEMY);
	m_pcMeleeRef->SetActiveState(false);
}

void CVikingController::GetPlayerReference()
{
	TEntityMessage message = TEntityMessage(0);
	m_pcTarget = CEventManager::SendEntityMessage(message)->GetComponent<CTransform>();
}

CVikingController & CVikingController::operator=(CVikingController & cCopy)
{
	m_pcTarget = cCopy.m_pcTarget;

	return *this;
}

CVikingController::~CVikingController()
{
}

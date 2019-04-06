#pragma once
#include "Component.h"

class CTransform;
class CProjectileEntity;
class CRigidbody;
class CAnimatorComponent;
class CStats;
class CInventory;

class CFireDemonController : public IComponent
{
	CRigidbody*				m_pcRigidbody;
	CTransform*				m_pcTransform;
	CTransform*				m_pEnemyTransform;
	CAnimatorComponent*		m_pcAnimator;
	CStats*					m_pcStats;
	CInventory*				m_pcInventory;

	float					m_fFireBallAttackTime;
	float					m_fMeleeAttacktime;
	float					m_fAttackAnimTime;
	float					m_fAoeAttackTime;
	float					m_fEnemyRadius;

	CProjectileEntity*		m_pcProjectileRef;
	CProjectileEntity*		m_pcMeleeRef;
	CProjectileEntity*		m_pcAOERef;

	bool					m_bIsAttacking;
	bool					m_bMoving;
	bool					m_bMouseControls;

	CMath::TVECTOR3			m_tClickPos;

	// Bool for debugging
	bool					m_bDebug;
public:
	CFireDemonController(IEntity* pcOwner);

	void Update();

	void Movement();

	void Melee();

	void Attack();

	void AOE(CMath::TVECTOR3 vPosition);

	void Init();

	CMath::TVECTOR3 GetAttackTime();

	void UseMouseControls(bool bMouseControls);

	~CFireDemonController();
};


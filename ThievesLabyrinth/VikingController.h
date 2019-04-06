#pragma once
#include "EnemyController.h"

class CTransform;
class CProjectileEntity;
class CRigidbody;
class CAnimatorComponent;
class CStats;

class CVikingController : public IEnemyController
{
	CTransform*				m_pcTransform;
	CTransform*				m_pcTarget;
	CRigidbody*				m_pcRigidbody;
	CAnimatorComponent*		m_pcAnimator;
	CStats*					m_pcStats;

	CProjectileEntity*		m_pcMeleeRef;

	float					m_fLastAttackTime;

	bool					m_bIsAttacking;

	void Attack();

	void Init();

public:
	CVikingController(IEntity* pcOwner);

	void Update();

	void GetPlayerReference();

	CVikingController& operator=(CVikingController& cCopy);

	~CVikingController();
};


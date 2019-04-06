#pragma once
#include "EnemyController.h"

class CTransform;
class CProjectileEntity;
class CRigidbody;
class CAnimatorComponent;
class CStats;

class CChickenController : public IEnemyController
{
	CProjectileEntity*		m_pcExplosion;
	CTransform*				m_pcTransform;
	CTransform*				m_pcTarget;
	CRigidbody*				m_pcRigidbody;
	//CAnimatorComponent*		m_pcAnimator;
	CStats*					m_pcStats;

	// Used to place the explosion in case the chicken dies
	CMath::TVECTOR3			m_tLastPos;

	bool					m_bExploding;
	
	void					Explode();

public:

	CChickenController(IEntity* pcOwner);

	void					Update();

	void					GetPlayerReference();

	CChickenController& operator=(CChickenController& cCopy);

	~CChickenController();
};


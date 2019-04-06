#pragma once
#include "Component.h"

class IEntity;

class IEnemyController : public IComponent
{
public:
	float m_fDeathTimer;

	IEnemyController(IEntity* pcOwner);

	virtual void Update() = 0;

	virtual void GetPlayerReference() = 0;

	int m_nEnemyType;

	float m_fSafeDistance;
};
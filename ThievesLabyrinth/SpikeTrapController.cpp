#include "SpikeTrapController.h"
#include "EnumTypes.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "Transform.h"

#include "Time.h"

CSpikeTrapController::CSpikeTrapController(IEntity* pcOwner) : IComponent(pcOwner)
{
	m_nComponentType = eComponent::SPIKE_TRAP_COMPONENT;
	m_pcCollider = m_pcOwner->GetComponent<CBoxCollider>();
	m_pcTransform = m_pcOwner->GetComponent<CTransform>();

	m_fCurrentTime = 0.0f;
	m_fCooldown = 2.0f;
	m_fActiveTime = 1.0f;
	m_fDamagePerHit = 2.0f;
}

void CSpikeTrapController::Update()
{
	if(m_bIsTrapActive)
	{
		if(m_fCurrentTime >= m_fActiveTime)
		{
			ToggleTrap();
			return;
		}
	}
	else
	{
		if(m_fCurrentTime >= m_fCooldown)
		{
			ToggleTrap();
			return;
		}

	}

	m_fCurrentTime += CTime::GetDelta();
}

void CSpikeTrapController::SetDamage(float fDamage)
{
	m_fDamagePerHit = fDamage;
}

float CSpikeTrapController::GetDamage()
{
	return m_fDamagePerHit;
}

void CSpikeTrapController::ToggleTrap()
{
	if(m_bIsTrapActive)
	{
		m_pcTransform->SetRotation(CMath::QuaternionFromAxisAngle({ 1, 0, 0 }, 180));
		m_pcCollider->SetActiveState(false);
	}
	else
	{
		m_pcTransform->SetRotation(CMath::QuaternionFromAxisAngle({ 1, 0, 0 }, 0));
		m_pcCollider->SetActiveState(true);
	}

	m_fCurrentTime = 0.0f;
	m_bIsTrapActive = !m_bIsTrapActive;
}

CSpikeTrapController& CSpikeTrapController::operator=(CSpikeTrapController & cToCopy)
{
	m_fActiveTime = cToCopy.m_fActiveTime;
	m_fCooldown = cToCopy.m_fCooldown;
	m_fCurrentTime = cToCopy.m_fCooldown;
	m_bIsTrapActive = cToCopy.m_bIsTrapActive;

	return *this;
}

CSpikeTrapController::~CSpikeTrapController()
{
}

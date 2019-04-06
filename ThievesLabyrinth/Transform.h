#pragma once
#include "Component.h"


class CTransform : public IComponent
{
	CMath::TMATRIX m_tMatrix;

	//CMath::TVECTOR3 m_tPosition;
	//CMath::TVECTOR4 m_tRotation;
	//CMath::TVECTOR3 m_tScale;

public:
	CTransform(IEntity* pcOwner);

	/***************
	* Accessors
	***************/

	CMath::TVECTOR3 GetPosition();
	CMath::TVECTOR4 GetRotation();
	CMath::TVECTOR3 GetScale();
	CMath::TMATRIX GetMatrix();

	/***************
	* Mutators
	***************/

	void SetPosition(CMath::TVECTOR3 tPosition);
	void SetRotation(CMath::TVECTOR4 tRotation);
	void SetScale(CMath::TVECTOR3 tScale);
	void SetMatrix(CMath::TMATRIX mMat);

	// Sets the forward vector to be the new forward
	void LookAt(CMath::TVECTOR3 newForward);

	// Smoothly transitions the forward vector to be set as the new forward
	void TurnTo(CMath::TVECTOR3 newForward, float = 10);
	// Smoothly transitions the forwards vector to point towards the target position
	void TurnTo(CTransform* target);

	void RenderTransform();

	CTransform& operator=(CTransform& cCopy);
	
	~CTransform();
};


#include "Transform.h"
#include "EventManager.h"
#include "EnumTypes.h"


CTransform::CTransform(IEntity* pcOwner) : IComponent(pcOwner)
{
	m_tMatrix = CMath::MatrixIdentity();

	m_nComponentType = eComponent::TRANSFORM;
	//m_tPosition = CMath::TVECTOR3(0, 0, 0);
	//m_tRotation = CMath::TVECTOR4(0, 0, 0, 1);
	//m_tScale = CMath::TVECTOR3(1, 1, 1);
}

CTransform::~CTransform()
{

}

void CTransform::SetPosition(CMath::TVECTOR3 tPosition)
{
	//m_tPosition = tPosition;
	m_tMatrix.r[3] = tPosition;
}

void CTransform::SetRotation(CMath::TVECTOR4 tRotation)
{
	CMath::TVECTOR3 tPosition, tScale;
	CMath::MatrixDecompose(&tScale , nullptr, &tPosition, m_tMatrix);
	m_tMatrix = CMath::MatrixScaleFromVector(tScale) * CMath::MatrixRotationQuaternion(tRotation);
	m_tMatrix.r[3] = tPosition;
}

void CTransform::SetScale(CMath::TVECTOR3 tScale)
{
	CMath::TVECTOR4 tRotation;
	CMath::TVECTOR3 tPosition;
	CMath::MatrixDecompose(nullptr, &tRotation, &tPosition, m_tMatrix);
	//m_tScale = tScale;
	m_tMatrix = CMath::MatrixScaleFromVector(tScale) * CMath::MatrixRotationQuaternion(tRotation);
	m_tMatrix.r[3] = tPosition;
}

void CTransform::SetMatrix(CMath::TMATRIX mMat)
{
	// set matrix
	m_tMatrix = mMat;
	// set position
	//m_tPosition = *(CMath::TVECTOR3*)&m_tMatrix.r[3];
	//// set scale
	//m_tMatrix.r[3] = { 0,0,0 };
	//m_tScale.x = CMath::Vector3Magnitude({ m_tMatrix.r[0].x, m_tMatrix.r[1].x, m_tMatrix.r[2].x });
	//m_tScale.y = CMath::Vector3Magnitude({ m_tMatrix.r[0].y, m_tMatrix.r[1].y, m_tMatrix.r[2].y });
	//m_tScale.z = CMath::Vector3Magnitude({ m_tMatrix.r[0].z, m_tMatrix.r[1].z, m_tMatrix.r[2].z });
	//m_tMatrix.r[3] = m_tPosition;
	//// set rotation
	//float tr = m_tMatrix.r[0].x + 1 + m_tMatrix.r[2].z;
	//
	//if (tr > 0)
	//{
	//	float S = sqrtf(tr + 1.0f) * 2; // S=4*m_tRotation.w 
	//	m_tRotation.w = 0.25f * S;
	//	m_tRotation.x = (m_tMatrix.r[2].y - 0) / S;
	//	m_tRotation.y = (m_tMatrix.r[0].z - m_tMatrix.r[2].x) / S;
	//	m_tRotation.z = (0 - m_tMatrix.r[0].y) / S;
	//}
	//else if ((m_tMatrix.r[0].x > 1) && (m_tMatrix.r[0].x > m_tMatrix.r[2].z))
	//{
	//	float S = sqrtf(1.0f + m_tMatrix.r[0].x - 1 - m_tMatrix.r[2].z) * 2; // S=4*m_tRotation.x 
	//	m_tRotation.w = (m_tMatrix.r[2].y - 0) / S;
	//	m_tRotation.x = 0.25f * S;
	//	m_tRotation.y = (m_tMatrix.r[0].y + 0) / S;
	//	m_tRotation.z = (m_tMatrix.r[0].z + m_tMatrix.r[2].x) / S;
	//}
	//else if (1 > m_tMatrix.r[2].z)
	//{
	//	float S = sqrtf(1.0f + 1 - m_tMatrix.r[0].x - m_tMatrix.r[2].z) * 2; // S=4*m_tRotation.y
	//	m_tRotation.w = (m_tMatrix.r[0].z - m_tMatrix.r[2].x) / S;
	//	m_tRotation.x = (m_tMatrix.r[0].y + 0) / S;
	//	m_tRotation.y = 0.25f * S;
	//	m_tRotation.z = (0 + m_tMatrix.r[2].y) / S;
	//}
	//else
	//{
	//	float S = sqrtf(1.0f + m_tMatrix.r[2].z - m_tMatrix.r[0].x - 1) * 2; // S=4*m_tRotation.z
	//	m_tRotation.w = (0 - m_tMatrix.r[0].y) / S;
	//	m_tRotation.x = (m_tMatrix.r[0].z + m_tMatrix.r[2].x) / S;
	//	m_tRotation.y = (0 + m_tMatrix.r[2].y) / S;
	//	m_tRotation.z = 0.25f * S;
	//}
}

CMath::TVECTOR3 CTransform::GetPosition()
{
	return *(CMath::TVECTOR3*)&m_tMatrix.r[3];
}

CMath::TVECTOR4 CTransform::GetRotation()
{
	CMath::TVECTOR4 tRotation;
	CMath::MatrixDecompose(nullptr, &tRotation, nullptr, m_tMatrix);
	return tRotation;
}

CMath::TVECTOR3 CTransform::GetScale()
{
	CMath::TVECTOR3 tScale;
	CMath::MatrixDecompose(&tScale, nullptr, nullptr, m_tMatrix);
	return tScale;
}

CMath::TMATRIX CTransform::GetMatrix()
{
	return m_tMatrix;
}

void CTransform::LookAt(CMath::TVECTOR3 newForward)
{
	CMath::TVECTOR3 x, y, z, vScale;
	CMath::MatrixDecompose(&vScale, nullptr, nullptr, m_tMatrix);

	z = CMath::Vector3Normalize(newForward - *(CMath::TVECTOR3*)&m_tMatrix.r[3]);
	x = CMath::Vector3Normalize(CMath::Vector3Cross(z, { 0,1,0 }));
	y = CMath::Vector3Normalize(CMath::Vector3Cross(x, z));
	m_tMatrix.r[0] = -x;
	m_tMatrix.r[1] = y;
	m_tMatrix.r[2] = z;
	m_tMatrix = CMath::MatrixScaleFromVector(vScale) * m_tMatrix;
	return;


	//CMath::TVECTOR3 forward = newForward;
	//CMath::TVECTOR3 up = CMath::TVECTOR3(0, 1, 0);
	//CMath::TVECTOR3 right = CMath::Vector3Cross(up, forward);
	//up = CMath::Vector3Cross(forward, right);

	//CMath::TVECTOR4 newRotation;
	//float tr = right.x + up.y + forward.z;

	//if (tr > 0)
	//{
	//	float S = sqrtf(tr + 1.0f) * 2; // S=4*newRotation.w 
	//	newRotation.w = 0.25f * S;
	//	newRotation.x = (forward.y - up.z) / S;
	//	newRotation.y = (right.z - forward.x) / S;
	//	newRotation.z = (up.x - right.y) / S;
	//}
	//else if ((right.x > up.y) && (right.x > forward.z))
	//{
	//	float S = sqrtf(1.0f + right.x - up.y - forward.z) * 2; // S=4*newRotation.x 
	//	newRotation.w = (forward.y - up.z) / S;
	//	newRotation.x = 0.25f * S;
	//	newRotation.y = (right.y + up.x) / S;
	//	newRotation.z = (right.z + forward.x) / S;
	//}
	//else if (up.y > forward.z)
	//{
	//	float S = sqrtf(1.0f + up.y - right.x - forward.z) * 2; // S=4*newRotation.y
	//	newRotation.w = (right.z - forward.x) / S;
	//	newRotation.x = (right.y + up.x) / S;
	//	newRotation.y = 0.25f * S;
	//	newRotation.z = (up.z + forward.y) / S;
	//}
	//else
	//{
	//	float S = sqrtf(1.0f + forward.z - right.x - up.y) * 2; // S=4*newRotation.z
	//	newRotation.w = (up.x - right.y) / S;
	//	newRotation.x = (right.z + forward.x) / S;
	//	newRotation.y = (up.z + forward.y) / S;
	//	newRotation.z = 0.25f * S;
	//}

	//this->SetRotation(newRotation);
}

void CTransform::TurnTo(CMath::TVECTOR3 vWhereToLook, float fSpeed)
{
	float fdx = CMath::Vector3Dot(vWhereToLook, m_tMatrix.r[0]);
	CMath::TVECTOR3 vPos;
	vPos = m_tMatrix.r[3];
	m_tMatrix.r[3] = { 0,0,0 };

	m_tMatrix = m_tMatrix * CMath::MatrixYRotation(TORAD(fdx) * fSpeed);
	m_tMatrix.r[3] = vPos;
}

void CTransform::TurnTo(CTransform * target)
{
	CMath::TVECTOR3 newForward = CMath::Vector3Normalize(*(CMath::TVECTOR3*)&(target->GetMatrix().r[3] - m_tMatrix.r[3]));
	TurnTo(newForward);
}

void CTransform::RenderTransform()
{
	CMath::TVECTOR4 tColors[3]{ { 1, 0, 0, 1}, { 0, 1, 0, 1}, { 0, 0, 1, 1} };

	CMath::TVECTOR3 tPosA{ *(CMath::TVECTOR3*)&m_tMatrix.r[3] };

	float fScaleFactor = 5;
	for (int i = 0; i < 3; i++)
	{
		TDebugLineMessage cVertex = TDebugLineMessage(tPosA, tColors[i]);
		CEventManager::SendDebugLineMessage(cVertex);

		CMath::TVECTOR3 tPosB{ tPosA.x + m_tMatrix.r[i].x * fScaleFactor,  tPosA.y + m_tMatrix.r[i].y * fScaleFactor,  tPosA.z + m_tMatrix.r[i].z * fScaleFactor };

		cVertex = TDebugLineMessage(tPosB, tColors[i]);
		CEventManager::SendDebugLineMessage(cVertex);

	}

}

CTransform & CTransform::operator=(CTransform & cCopy)
{
	//m_tPosition = cCopy.GetPosition();
	//m_tRotation = cCopy.GetRotation();
	//m_tScale = cCopy.GetScale();
	m_tMatrix = cCopy.GetMatrix();

	return *this;
}


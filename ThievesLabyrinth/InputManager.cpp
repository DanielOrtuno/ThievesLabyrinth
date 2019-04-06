#pragma once
#include "InputManager.h"
#include "EventManager.h"

#include "Transform.h"

#include <DirectXMath.h>
#include <windowsx.h>
#include <iostream>

std::bitset<NBITSIZE> CInputManager::m_bKeysDown;
std::bitset<NBITSIZE> CInputManager::m_bKeyPresses(0xffffffffff);
std::bitset<NBITSIZE> CInputManager::m_bKeyBools(0xffffffffff);
int CInputManager::nMouseXPos = 0;
int CInputManager::nMouseYPos = 0;
int CInputManager::nScreenWidth = 0;
int CInputManager::nScreenHeight = 0;
int CInputManager::nXDiff = 0;
int CInputManager::nYDiff = 0;
const CMath::TMATRIX* CInputManager::m_pProjMat;
CTransform* CInputManager::m_pCameraTransform;
RECT CInputManager::m_WindowBox;
bool CInputManager::m_bUpdateScroll;
int CInputManager::m_nScrollDirection;

bool CInputManager::GetKey(char chKey)		
{
	switch (chKey)
	{
	case 'W':
	{
		if (m_bKeysDown[0] == 1)		//Every if statement requires brackets 
			return true;
		break;
	}
	case 'A':
	{
		if (m_bKeysDown[1] == 1)
			return true;
		break;
	}
	case 'S':
	{
		if (m_bKeysDown[2] == 1)
			return true;
		break;
	}
	case 'D':
	{
		if (m_bKeysDown[3] == 1)
			return true;
		break;
	}
	case VK_LBUTTON:
	{
		if (m_bKeysDown[4] == 1)
			return true;
		break;
	}
	case VK_UP:
	{
		if (m_bKeysDown[5] == 1)
			return true;
		break;
	}
	case VK_LEFT:
	{
		if (m_bKeysDown[6] == 1)
			return true;
		break;
	}
	case VK_DOWN:
	{
		if (m_bKeysDown[7] == 1)
			return true;
		break;
	}
	case VK_RIGHT:
	{
		if (m_bKeysDown[8] == 1)
			return true;
		break;
	}
	case 'B':
	{
		if (m_bKeysDown[9] == 1)
			return true;
		break;
	}
	case 'C':
	{
		if (m_bKeysDown[10] == 1)
			return true;
		break;
	}
	case 'E':
	{
		if (m_bKeysDown[11] == 1)
			return true;
		break;
	}
	case 'F':
	{
		if (m_bKeysDown[12] == 1)
			return true;
		break;
	}
	case 'G':
	{
		if (m_bKeysDown[13] == 1)
			return true;
		break;
	}
	case 'H':
	{
		if (m_bKeysDown[14] == 1)
			return true;
		break;
	}
	case 'I':
	{
		if (m_bKeysDown[15] == 1)
			return true;
		break;
	}
	case 'J':
	{
		if (m_bKeysDown[16] == 1)
			return true;
		break;
	}
	case 'K':
	{
		if (m_bKeysDown[17] == 1)
			return true;
		break;
	}
	case 'L':
	{
		if (m_bKeysDown[18] == 1)
			return true;
		break;
	}
	case 'M':
	{
		if (m_bKeysDown[19] == 1)
			return true;
		break;
	}
	case 'N':
	{
		if (m_bKeysDown[20] == 1)
			return true;
		break;
	}
	case 'O':
	{
		if (m_bKeysDown[21] == 1)
			return true;
		break;
	}
	case 'P':
	{
		if (m_bKeysDown[22] == 1)
			return true;
		break;
	}
	case 'Q':
	{
		if (m_bKeysDown[23] == 1)
			return true;
		break;
	}
	case 'R':
	{
		if (m_bKeysDown[24] == 1)
			return true;
		break;
	}
	case 'T':
	{
		if (m_bKeysDown[25] == 1)
			return true;
		break;
	}
	case 'U':
	{
		if (m_bKeysDown[26] == 1)
			return true;
		break;
	}
	case 'V':
	{
		if (m_bKeysDown[27] == 1)
			return true;
		break;
	}
	case 'X':
	{
		if (m_bKeysDown[28] == 1)
			return true;
		break;
	}
	case 'Y':
	{
		if (m_bKeysDown[29] == 1)
			return true;
		break;
	}
	case 'Z':
	{
		if (m_bKeysDown[30] == 1)
			return true;
		break;
	}
	case VK_ESCAPE:
	{
		if (m_bKeysDown[31] == 1)
			return true;
		break;
	}
	case VK_RBUTTON:
	{
		if (m_bKeysDown[32] == 1)
			return true;
		break;
	}
	case '1':
	{
		if (m_bKeysDown[33] == 1)
			return true;
		break;
	}
	case '2':
	{
		if (m_bKeysDown[34] == 1)
			return true;
		break;
	}
	case '3':
	{
		if (m_bKeysDown[35] == 1)
			return true;
		break;
	}
	case VK_SPACE:
	{
		if (m_bKeysDown[36] == 1)
			return true;
		break;
	}
	case VK_TAB:
	{
		if (m_bKeysDown[37] == 1)
			return true;
		break;
	}
	case VK_F1:
	{
		if (m_bKeysDown[38] == 1)
			return true;
		break;
	}
	case VK_F2:
	{
		if (m_bKeysDown[39] == 1)
			return true;
		break;
	}
	case VK_F3:
	{
		if (m_bKeysDown[40] == 1)
			return true;
		break;
	}
	case VK_F4:
	{
		if (m_bKeysDown[41] == 1)
			return true;
		break;
	}
	case VK_F5:
	{
		if (m_bKeysDown[42] == 1)
			return true;
		break;
	}
	case VK_F6:
	{
		if (m_bKeysDown[43] == 1)
			return true;
		break;
	}
	case VK_F7:
	{
		if (m_bKeysDown[44] == 1)
			return true;
		break;
	}
	case VK_F8:
	{
		if (m_bKeysDown[45] == 1)
			return true;
		break;
	}
	case VK_F9:
	{
		if (m_bKeysDown[46] == 1)
			return true;
		break;
	}
	case VK_PRIOR:
	{
		if (m_bKeysDown[47] == 1)
			return true;
		break;
	}
	case VK_F11:
	{
		if (m_bKeysDown[48] == 1)
			return true;
		break;
	}
	case VK_NEXT:
	{
		if (m_bKeysDown[49] == 1)
			return true;
		break;
	}
	case VK_CONTROL:
	{
		if (m_bKeysDown[50] == 1)
			return true;
		break;

	}
	default:
		break;
	}
	return false;
};

bool CInputManager::GetKeyDown(char chKey)
{
	switch (chKey)
	{
	case 'W':
	{
		if ((m_bKeysDown[0] == 1) && (m_bKeyPresses[0] == 1))
		{
			m_bKeyBools[0] = 0;
			return true;
		}
		break;
	}
	case 'A':
	{
		if ((m_bKeysDown[1] == 1) && (m_bKeyPresses[1] == 1))
		{
			m_bKeyBools[1] = 0;
			return true;
		}
		break;
	}
	case 'S':
	{
		if ((m_bKeysDown[2] == 1) && (m_bKeyPresses[2] == 1))
		{
			m_bKeyBools[2] = 0;
			return true;
		}
		break;
	}
	case 'D':
	{
		if ((m_bKeysDown[3] == 1) && (m_bKeyPresses[3] == 1))
		{
			m_bKeyBools[3] = 0;
			return true;
		}
		break;
	}
	case VK_LBUTTON:
	{
		if ((m_bKeysDown[4] == 1) && (m_bKeyPresses[4] == 1))
		{
			m_bKeyBools[4] = 0;
			return true;
		}
		break;
	}
	case VK_UP:
	{
		if ((m_bKeysDown[5] == 1) && (m_bKeyPresses[5] == 1))
		{
			m_bKeyBools[5] = 0;
			return true;
		}
		break;
	}
	case VK_LEFT:
	{
		if ((m_bKeysDown[6] == 1) && (m_bKeyPresses[6] == 1))
		{
			m_bKeyBools[6] = 0;
			return true;
		}
		break;
	}
	case VK_DOWN:
	{
		if ((m_bKeysDown[7] == 1) && (m_bKeyPresses[7] == 1))
		{
			m_bKeyBools[7] = 0;
			return true;
		}
		break;
	}
	case VK_RIGHT:
	{
		if ((m_bKeysDown[8] == 1) && (m_bKeyPresses[8] == 1))
		{
			m_bKeyBools[8] = 0;
			return true;
		}
		break;
	}
	case 'B':
	{
		if ((m_bKeysDown[9] == 1) && (m_bKeyPresses[9] == 1))
		{
			m_bKeyBools[9] = 0;
			return true;
		}
		break;
	}
	case 'C':
	{
		if ((m_bKeysDown[10] == 1) && (m_bKeyPresses[10] == 1))
		{
			m_bKeyBools[10] = 0;
			return true;
		}
		break;
	}
	case 'E':
	{
		if ((m_bKeysDown[11] == 1) && (m_bKeyPresses[11] == 1))
		{
			m_bKeyBools[11] = 0;
			return true;
		}
		break;
	}
	case 'F':
	{
		if ((m_bKeysDown[12] == 1) && (m_bKeyPresses[12] == 1))
		{
			m_bKeyBools[12] = 0;
			return true;
		}
		break;
	}
	case 'G':
	{
		if ((m_bKeysDown[13] == 1) && (m_bKeyPresses[13] == 1))
		{
			m_bKeyBools[13] = 0;
			return true;
		}
		break;
	}
	case 'H':
	{
		if ((m_bKeysDown[14] == 1) && (m_bKeyPresses[14] == 1))
		{
			m_bKeyBools[14] = 0;
			return true;
		}
		break;
	}
	case 'I':
	{
		if ((m_bKeysDown[15] == 1) && (m_bKeyPresses[15] == 1))
		{
			m_bKeyBools[15] = 0;
			return true;
		}
		break;
	}
	case 'J':
	{
		if ((m_bKeysDown[16] == 1) && (m_bKeyPresses[16] == 1))
		{
			m_bKeyBools[16] = 0;
			return true;
		}
		break;
	}
	case 'K':
	{
		if ((m_bKeysDown[17] == 1) && (m_bKeyPresses[17] == 1))
		{
			m_bKeyBools[17] = 0;
			return true;
		}
		break;
	}
	case 'L':
	{
		if ((m_bKeysDown[18] == 1) && (m_bKeyPresses[18] == 1))
		{
			m_bKeyBools[18] = 0;
			return true;
		}
		break;
	}
	case 'M':
	{
		if ((m_bKeysDown[19] == 1) && (m_bKeyPresses[19] == 1))
		{
			m_bKeyBools[19] = 0;
			return true;
		}
		break;
	}
	case 'N':
	{
		if ((m_bKeysDown[20] == 1) && (m_bKeyPresses[20] == 1))
		{
			m_bKeyBools[20] = 0;
			return true;
		}
		break;
	}
	case 'O':
	{
		if ((m_bKeysDown[21] == 1) && (m_bKeyPresses[21] == 1))
		{
			m_bKeyBools[21] = 0;
			return true;
		}
		break;
	}
	case 'P':
	{
		if ((m_bKeysDown[22] == 1) && (m_bKeyPresses[22] == 1))
		{
			m_bKeyBools[22] = 0;
			return true;
		}
		break;
	}
	case 'Q':
	{
		if ((m_bKeysDown[23] == 1) && (m_bKeyPresses[23] == 1))
		{
			m_bKeyBools[23] = 0;
			return true;
		}
		break;
	}
	case 'R':
	{
		if ((m_bKeysDown[24] == 1) && (m_bKeyPresses[24] == 1))
		{
			m_bKeyBools[24] = 0;
			return true;
		}
		break;
	}
	case 'T':
	{
		if ((m_bKeysDown[25] == 1) && (m_bKeyPresses[25] == 1))
		{
			m_bKeyBools[25] = 0;
			return true;
		}
		break;
	}
	case 'U':
	{
		if ((m_bKeysDown[26] == 1) && (m_bKeyPresses[26] == 1))
		{
			m_bKeyBools[26] = 0;
			return true;
		}
		break;
	}
	case 'V':
	{
		if ((m_bKeysDown[27] == 1) && (m_bKeyPresses[27] == 1))
		{
			m_bKeyBools[27] = 0;
			return true;
		}
		break;
	}
	case 'X':
	{
		if ((m_bKeysDown[28] == 1) && (m_bKeyPresses[28] == 1))
		{
			m_bKeyBools[28] = 0;
			return true;
		}
		break;
	}
	case 'Y':
	{
		if ((m_bKeysDown[29] == 1) && (m_bKeyPresses[29] == 1))
		{
			m_bKeyBools[29] = 0;
			return true;
		}
		break;
	}
	case 'Z':
	{
		if ((m_bKeysDown[30] == 1) && (m_bKeyPresses[30] == 1))
		{
			m_bKeyBools[30] = 0;
			return true;
		}
		break;
	}
	case VK_ESCAPE:
	{
		if ((m_bKeysDown[31] == 1) && (m_bKeyPresses[31] == 1))
		{
			m_bKeyBools[31] = 0;
			return true;
		}
		break;
	}
	case VK_RBUTTON:
	{
		if ((m_bKeysDown[32] == 1) && (m_bKeyPresses[32] == 1))
		{
			m_bKeyBools[32] = 0;
			return true;
		}
		break;
	}
	case '1':
	{
		if ((m_bKeysDown[33] == 1) && (m_bKeyPresses[33] == 1))
		{
			m_bKeyBools[33] = 0;
			return true;
		}
		break;
	}
	case '2':
	{
		if ((m_bKeysDown[34] == 1) && (m_bKeyPresses[34] == 1))
		{
			m_bKeyBools[34] = 0;
			return true;
		}
		break;
	}
	case '3':
	{
		if ((m_bKeysDown[35] == 1) && (m_bKeyPresses[35] == 1))
		{
			m_bKeyBools[35] = 0;
			return true;
		}
		break;
	}
	case VK_SPACE:
	{
		if ((m_bKeysDown[36] == 1) && (m_bKeyPresses[36] == 1))
		{
			m_bKeyBools[36] = 0;
			return true;
		}
		break;
	}
	case VK_TAB:
	{
		if ((m_bKeysDown[37] == 1) && (m_bKeyPresses[37] == 1))
		{
			m_bKeyBools[37] = 0;
			return true;
		}
		break;
	}
	case VK_F1:
	{
		if ((m_bKeysDown[38] == 1) && (m_bKeyPresses[38] == 1))
		{
			m_bKeyBools[38] = 0;
			return true;
		}
		break;
	}
	case VK_F2:
	{
		if ((m_bKeysDown[39] == 1) && (m_bKeyPresses[39] == 1))
		{
			m_bKeyBools[39] = 0;
			return true;
		}
		break;
	}
	case VK_F3:
	{
		if ((m_bKeysDown[40] == 1) && (m_bKeyPresses[40] == 1))
		{
			m_bKeyBools[40] = 0;
			return true;
		}
		break;
	}
	case VK_F4:
	{
		if ((m_bKeysDown[41] == 1) && (m_bKeyPresses[41] == 1))
		{
			m_bKeyBools[41] = 0;
			return true;
		}
		break;
	}
	case VK_F5:
	{
		if ((m_bKeysDown[42] == 1) && (m_bKeyPresses[42] == 1))
		{
			m_bKeyBools[42] = 0;
			return true;
		}
		break;
	}
	case VK_F6:
	{
		if ((m_bKeysDown[43] == 1) && (m_bKeyPresses[43] == 1))
		{
			m_bKeyBools[43] = 0;
			return true;
		}
		break;
	}
	case VK_F7:
	{
		if ((m_bKeysDown[44] == 1) && (m_bKeyPresses[44] == 1))
		{
			m_bKeyBools[44] = 0;
			return true;
		}
		break;
	}
	case VK_F8:
	{
		if ((m_bKeysDown[45] == 1) && (m_bKeyPresses[45] == 1))
		{
			m_bKeyBools[45] = 0;
			return true;
		}
		break;
	}
	case VK_F9:
	{
		if ((m_bKeysDown[46] == 1) && (m_bKeyPresses[46] == 1))
		{
			m_bKeyBools[46] = 0;
			return true;
		}
		break;
	}
	case VK_PRIOR:
	{
		if ((m_bKeysDown[47] == 1) && (m_bKeyPresses[47] == 1))
		{
			m_bKeyBools[47] = 0;
			return true;
		}
		break;
	}
	case VK_F11:
	{
		if ((m_bKeysDown[48] == 1) && (m_bKeyPresses[48] == 1))
		{
			m_bKeyBools[48] = 0;
			return true;
		}
		break;
	}
	case VK_NEXT:
	{
		if ((m_bKeysDown[49] == 1) && (m_bKeyPresses[49] == 1))
		{
			m_bKeyBools[49] = 0;
			return true;
		}
		break;
	}
	case VK_CONTROL:
	{
		if ((m_bKeysDown[50] == 1) && (m_bKeyPresses[50] == 1))
		{
			m_bKeyBools[50] = 0;
			return true;
		}
		break;
	}
	default:
		break;
	}
	return false;
};

void CInputManager::UpdatePresses()
{
	for (int i = 0; i < NBITSIZE; i++)
	{
		m_bKeyPresses[i] = m_bKeyBools[i];
	}
	if (m_bUpdateScroll)
	{
		m_nScrollDirection = 0;
	}
}

void CInputManager::SetMouseToCenter()
{
	SetCursorPos(m_WindowBox.left + ((m_WindowBox.right - m_WindowBox.left) / 2), (m_WindowBox.top + ((m_WindowBox.bottom - m_WindowBox.top) / 2)));
}

int CInputManager::GetScrollDirection()
{
	m_bUpdateScroll = true;
	return m_nScrollDirection;
}

void CInputManager::GetMousePos(int& nMouseX, int& nMouseY)
{
	nMouseX = nMouseXPos;
	nMouseY = nMouseYPos;
}

void CInputManager::GetMousePosNDC(float & _nX, float & _nY)
{
	_nX = (nMouseXPos / (nScreenWidth / 2.0f)) - 1;
	_nY = (-nMouseYPos / (nScreenHeight / 2.0f)) + 1;
}

void CInputManager::GetScreenWH(int & nWidth, int & nHeight)
{
	nWidth = nScreenWidth;
	nHeight = nScreenHeight;
}

void CInputManager::SetViewTransform(CTransform & _mView)
{
	m_pCameraTransform = &_mView;
}

void CInputManager::SetProjMat(CMath::TMATRIX & _mProj)
{
	m_pProjMat = &_mProj;
}

void CInputManager::GetMouseWorldSpace(const CMath::TVECTOR2 & vScreenSpacePosition, CMath::TVECTOR3 & vWorldStart, CMath::TVECTOR3 & vWorldEnd)
{
	CMath::TVECTOR4 vScreenStart(vScreenSpacePosition.x, vScreenSpacePosition.y, 0.0f, 1.0f);
	CMath::TVECTOR4 vScreenEnd	(vScreenSpacePosition.x, vScreenSpacePosition.y, 1.0f, 1.0f);
	
	CMath::TMATRIX mProjectionInverse, mViewProjection;
	mProjectionInverse = CMath::MatrixInverse(*m_pProjMat);
	mViewProjection = mProjectionInverse * m_pCameraTransform->GetMatrix();

	CMath::TVECTOR4 vWorldStart4, vWorldEnd4;
	vWorldStart4 = CMath::Vector4Transform(vScreenStart, mViewProjection);
	vWorldEnd4	 = CMath::Vector4Transform(vScreenEnd, mViewProjection);

	vWorldStart	= *(CMath::TVECTOR3*)&vWorldStart4;
	vWorldEnd	= *(CMath::TVECTOR3*)&vWorldEnd4;
	vWorldStart	/= vWorldStart4.w;
	vWorldEnd	/= vWorldEnd4.w;
}

LRESULT CALLBACK CInputManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		if (wParam == 'W')
			m_bKeysDown[0] = 1;
		if (wParam == 'A')
			m_bKeysDown[1] = 1;
		if (wParam == 'S')
			m_bKeysDown[2] = 1;
		if (wParam == 'D')
			m_bKeysDown[3] = 1;
		if (wParam == VK_UP)
			m_bKeysDown[5] = 1;
		if (wParam == VK_LEFT)
			m_bKeysDown[6] = 1;
		if (wParam == VK_DOWN)
			m_bKeysDown[7] = 1;
		if (wParam == VK_RIGHT)
			m_bKeysDown[8] = 1;
		if (wParam == 'B')
			m_bKeysDown[9] = 1;
		if (wParam == 'C')
			m_bKeysDown[10] = 1;
		if (wParam == 'E')
			m_bKeysDown[11] = 1;
		if (wParam == 'F')
			m_bKeysDown[12] = 1;
		if (wParam == 'G')
			m_bKeysDown[13] = 1;
		if (wParam == 'H')
			m_bKeysDown[14] = 1;
		if (wParam == 'I')
			m_bKeysDown[15] = 1;
		if (wParam == 'J')
			m_bKeysDown[16] = 1;
		if (wParam == 'K')
			m_bKeysDown[17] = 1;
		if (wParam == 'L')
			m_bKeysDown[18] = 1;
		if (wParam == 'M')
			m_bKeysDown[19] = 1;
		if (wParam == 'N')
			m_bKeysDown[20] = 1;
		if (wParam == 'O')
			m_bKeysDown[21] = 1;
		if (wParam == 'P')
			m_bKeysDown[22] = 1;
		if (wParam == 'Q')
			m_bKeysDown[23] = 1;
		if (wParam == 'R')
			m_bKeysDown[24] = 1;
		if (wParam == 'T')
			m_bKeysDown[25] = 1;
		if (wParam == 'U')
			m_bKeysDown[26] = 1;
		if (wParam == 'V')
			m_bKeysDown[27] = 1;
		if (wParam == 'X')
			m_bKeysDown[28] = 1;
		if (wParam == 'Y')
			m_bKeysDown[29] = 1;
		if (wParam == 'Z')
			m_bKeysDown[30] = 1;
		if (wParam == VK_ESCAPE)
			m_bKeysDown[31] = 1;
		if (wParam == '1')
			m_bKeysDown[33] = 1;
		if (wParam == '2')
			m_bKeysDown[34] = 1;
		if (wParam == '3')
			m_bKeysDown[35] = 1;
		if (wParam == VK_SPACE)
			m_bKeysDown[36] = 1;
		if (wParam == VK_TAB)
			m_bKeysDown[37] = 1;
		if (wParam == VK_F1)
			m_bKeysDown[38] = 1;
		if (wParam == VK_F2)
			m_bKeysDown[39] = 1;
		if (wParam == VK_F3)
			m_bKeysDown[40] = 1;
		if (wParam == VK_F4)
			m_bKeysDown[41] = 1;
		if (wParam == VK_F5)
			m_bKeysDown[42] = 1;
		if (wParam == VK_F6)
			m_bKeysDown[43] = 1;
		if (wParam == VK_F7)
			m_bKeysDown[44] = 1;
		if (wParam == VK_F8)
			m_bKeysDown[45] = 1;
		if (wParam == VK_F9)
			m_bKeysDown[46] = 1;
		if (wParam == VK_PRIOR)
			m_bKeysDown[47] = 1;
		if (wParam == VK_F11)
			m_bKeysDown[48] = 1;
		if (wParam == VK_NEXT)
			m_bKeysDown[49] = 1;
		if (wParam == VK_CONTROL)
			m_bKeysDown[50] = 1;
		break;
	}
	case WM_KEYUP:
	{
		if (wParam == 'W')
		{
			m_bKeysDown[0] = 0;
			m_bKeyBools[0] = 1;
		}
		if (wParam == 'A')
		{
			m_bKeysDown[1] = 0;
			m_bKeyBools[1] = 1;
		}		
		if (wParam == 'S')
		{
			m_bKeysDown[2] = 0;
			m_bKeyBools[2] = 1;
		}
		if (wParam == 'D')
		{
			m_bKeysDown[3] = 0;
			m_bKeyBools[3] = 1;
		}
		if (wParam == VK_UP)
		{
			m_bKeysDown[5] = 0;
			m_bKeyBools[5] = 1;
		}
		if (wParam == VK_LEFT)
		{
			m_bKeysDown[6] = 0;
			m_bKeyBools[6] = 1;
		}
		if (wParam == VK_DOWN)
		{
			m_bKeysDown[7] = 0;
			m_bKeyBools[7] = 1;
		}
		if (wParam == VK_RIGHT)
		{
			m_bKeysDown[8] = 0;
			m_bKeyBools[8] = 1;
		}
		if (wParam == 'B')
		{
			m_bKeysDown[9] = 0;
			m_bKeyBools[9] = 1;
		}
		if (wParam == 'C')
		{
			m_bKeysDown[10] = 0;
			m_bKeyBools[10] = 1;
		}
		if (wParam == 'E')
		{
			m_bKeysDown[11] = 0;
			m_bKeyBools[11] = 1;
		}
		if (wParam == 'F')
		{
			m_bKeysDown[12] = 0;
			m_bKeyBools[12] = 1;
		}
		if (wParam == 'G')
		{
			m_bKeysDown[13] = 0;
			m_bKeyBools[13] = 1;
		}
		if (wParam == 'H')
		{
			m_bKeysDown[14] = 0;
			m_bKeyBools[14] = 1;
		}
		if (wParam == 'I')
		{
			m_bKeysDown[15] = 0;
			m_bKeyBools[15] = 1;
		}
		if (wParam == 'J')
		{
			m_bKeysDown[16] = 0;
			m_bKeyBools[16] = 1;
		}
		if (wParam == 'K')
		{
			m_bKeysDown[17] = 0;
			m_bKeyBools[17] = 1;
		}
		if (wParam == 'L')
		{
			m_bKeysDown[18] = 0;
			m_bKeyBools[18] = 1;
		}
		if (wParam == 'M')
		{
			m_bKeysDown[19] = 0;
			m_bKeyBools[19] = 1;
		}
		if (wParam == 'N')
		{
			m_bKeysDown[20] = 0;
			m_bKeyBools[20] = 1;
		}		
		if (wParam == 'O')
		{
			m_bKeysDown[21] = 0;
			m_bKeyBools[21] = 1;
		}
		if (wParam == 'P')
		{
			m_bKeysDown[22] = 0;
			m_bKeyBools[22] = 1;
		}
		if (wParam == 'Q')
		{
			m_bKeysDown[23] = 0;
			m_bKeyBools[23] = 1;
		}
		if (wParam == 'R')
		{
			m_bKeysDown[24] = 0;
			m_bKeyBools[24] = 1;
		}
		if (wParam == 'T')
		{
			m_bKeysDown[25] = 0;
			m_bKeyBools[25] = 1;
		}
		if (wParam == 'U')
		{
			m_bKeysDown[26] = 0;
			m_bKeyBools[26] = 1;
		}
		if (wParam == 'V')
		{
			m_bKeysDown[27] = 0;
			m_bKeyBools[27] = 1;
		}
		if (wParam == 'X')
		{
			m_bKeysDown[28] = 0;
			m_bKeyBools[28] = 1;
		}
		if (wParam == 'Y')
		{
			m_bKeysDown[29] = 0;
			m_bKeyBools[29] = 1;
		}
		if (wParam == 'Z')
		{
			m_bKeysDown[30] = 0;
			m_bKeyBools[30] = 1;
		}
		if (wParam == VK_ESCAPE)
		{
			m_bKeysDown[31] = 0;
			m_bKeyBools[31] = 1;
		}
		if (wParam == '1')
		{
			m_bKeysDown[33] = 0;
			m_bKeyBools[33] = 1;
		}
		if (wParam == '2')
		{
			m_bKeysDown[34] = 0;
			m_bKeyBools[34] = 1;
		}
		if (wParam == '3')
		{
			m_bKeysDown[35] = 0;
			m_bKeyBools[35] = 1;
		}
		if (wParam == VK_SPACE)
		{
			m_bKeysDown[36] = 0;
			m_bKeyBools[36] = 1;
		}
		if (wParam == VK_TAB)
		{
			m_bKeysDown[37] = 0;
			m_bKeyBools[37] = 1;
		}
		if (wParam == VK_F1)
		{
			m_bKeysDown[38] = 0;
			m_bKeyBools[38] = 1;
		}
		if (wParam == VK_F2)
		{
			m_bKeysDown[39] = 0;
			m_bKeyBools[39] = 1;
		}
		if (wParam == VK_F3)
		{
			m_bKeysDown[40] = 0;
			m_bKeyBools[40] = 1;
		}
		if (wParam == VK_F4)
		{
			m_bKeysDown[41] = 0;
			m_bKeyBools[41] = 1;
		}
		if (wParam == VK_F5)
		{
			m_bKeysDown[42] = 0;
			m_bKeyBools[42] = 1;
		}
		if (wParam == VK_F6)
		{
			m_bKeysDown[43] = 0;
			m_bKeyBools[43] = 1;
		}
		if (wParam == VK_F7)
		{
			m_bKeysDown[44] = 0;
			m_bKeyBools[44] = 1;
		}
		if (wParam == VK_F8)
		{
			m_bKeysDown[45] = 0;
			m_bKeyBools[45] = 1;
		}
		if (wParam == VK_F9)
		{
			m_bKeysDown[46] = 0;
			m_bKeyBools[46] = 1;
		}
		if (wParam == VK_PRIOR)
		{
			m_bKeysDown[47] = 0;
			m_bKeyBools[47] = 1;
		}
		if (wParam == VK_F11)
		{
			m_bKeysDown[48] = 0;
			m_bKeyBools[48] = 1;
		}
		if (wParam == VK_NEXT)
		{
			m_bKeysDown[49] = 0;
			m_bKeyBools[49] = 1;
		}
		if (wParam == VK_CONTROL)
		{
			m_bKeysDown[50] = 0;
			m_bKeyBools[50] = 1;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		m_bKeysDown[4] = 1;
		break;
	}
	case WM_LBUTTONUP:
	{
		m_bKeysDown[4] = 0;
		m_bKeyBools[4] = 1;
		break;
	}
	case WM_RBUTTONDOWN:
	{
		m_bKeysDown[32] = 1;
		break;
	}
	case WM_RBUTTONUP:
	{
		m_bKeysDown[32] = 0;
		m_bKeyBools[32] = 1;
		break;
	}
	case WM_MOUSEMOVE:
	{
		nXDiff = nMouseXPos;
		nYDiff = nMouseYPos;
		nMouseXPos = GET_X_LPARAM(lParam);
		nMouseYPos = GET_Y_LPARAM(lParam);
		if (!m_bKeysDown[32])
		{
			nXDiff = nMouseXPos;
			nYDiff = nMouseYPos;
		}
		break;
	}
	case WM_SIZE:
	{
		nScreenWidth = LOWORD(lParam);
		nScreenHeight = HIWORD(lParam);
		// Call function to event manager
		// To resize all the stuff
		CEventManager::SendResizeMessage(TWindowResizeMessage(nScreenWidth, nScreenHeight));
		break;
	}
	case WM_MOUSEWHEEL:
	{
		short direction = HIWORD(wParam);
		if (direction > 0)
		{
			m_nScrollDirection = 1;
		}
		else if (direction < 0)
		{
			m_nScrollDirection = -1;
		}
		else
		{
			m_nScrollDirection = 0;
		}
		m_bUpdateScroll = false;
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	}
	CInputManager::UpdatePresses();
	GetWindowRect(hWnd, &m_WindowBox);
	return 0;
}

void CInputManager::GetMouseDelta(int& nDiffX, int& nDiffY)
{
	nDiffX = nMouseXPos - nXDiff;
	nDiffY = nMouseYPos - nYDiff;

	nXDiff = nMouseXPos;
	nYDiff = nMouseYPos;
}
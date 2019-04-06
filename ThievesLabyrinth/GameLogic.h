#pragma once
#include "InputManager.h"
#include <windowsx.h>
#include <tchar.h>

#define CHEATCODES

class CComponentManager;
class CEntityManager;
class CEventManager;
class CAudioManager;
class CRenderManager;
class CPhysicsManager;
class CLevelManager;
class CAIManager;
class CTime;

class CGameLogic : public ISystem
{
private:
	CComponentManager* m_pcComponentManager;
	static CEntityManager* m_pcEntityManager;
	CEventManager* m_pcEventManager;
	CAudioManager* m_pcAudioManager;
	static CRenderManager* m_pcRenderManager;
	CPhysicsManager* m_pcPhysicsManager;
	static CLevelManager* m_pcLevelManager;
	CAIManager* m_pcAIManager;
	CTime* m_cTime;
	static int m_nCurrentState;
	static bool m_bStateInitialized;
	static bool m_bMouseControls;

#ifdef CHEATCODES
	bool bGodMode = false;
	bool bInfiniteMana = false;
	bool bRefillHealth = false;
#endif // CHEATCODES

	void LoadSettings();
	void SaveSettings();
public:
	CGameLogic(HWND cWindow);
	~CGameLogic();

	void Update();
	void BuildOptionsMenus();

	static void StartGame();
	static void ExitGame();
	static void TogglePause();
	static void GoBackToMain();
	static void PlayButtonSound();
	static void StartToOptions();
	static void PauseToOptions();
	static void ToPause();
	static void ToStart();

	static void SwapControls();

};

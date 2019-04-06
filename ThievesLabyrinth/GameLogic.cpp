#include "GameLogic.h"
#include "LevelManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "AIManager.h"
#include "DebugManager.h"
#include "MeshRenderer.h"
#include "RenderManager.h"
#include "GUIManager.h"

#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "AnimatorComponent.h"
#include "Entity.h"
#include "Stats.h"
#include "Transform.h"
#include "FireDemonController.h"

#include "Time.h"

int CGameLogic::m_nCurrentState;
bool CGameLogic::m_bStateInitialized;
bool CGameLogic::m_bMouseControls;
CRenderManager* CGameLogic::m_pcRenderManager;
CLevelManager* CGameLogic::m_pcLevelManager;
CEntityManager* CGameLogic::m_pcEntityManager;

void CGameLogic::LoadSettings()
{
	std::ifstream file("Settings.txt", std::ios_base::in);
	if (file.is_open())
	{
		// Read in Audio settings
		float fVolume;
		file >> fVolume;
		m_pcAudioManager->ChangeMasterVol(fVolume);
		file >> fVolume;
		m_pcAudioManager->ChangeMusicVol(fVolume);
		file >> fVolume;
		m_pcAudioManager->ChangeSFXVol(fVolume);

		// Read in control settings
		file >> m_bMouseControls;

		// Update options menu
		CGUIManager::SetControls(m_bMouseControls);
	}
	else
	{
		// Defualt audio settings
		m_pcAudioManager->ChangeMusicVol(1.0f);
		m_pcAudioManager->ChangeMasterVol(1.0f);
		m_pcAudioManager->ChangeSFXVol(1.0f);

		// Default control settings
		m_bMouseControls = true;

		// Update options menu
		CGUIManager::SetControls(m_bMouseControls);
	}
	file.close();
}

void CGameLogic::SaveSettings()
{
	std::ofstream file("Settings.txt");
	if (file.is_open())
	{
		// Write out audio settings
		file << std::to_string(m_pcAudioManager->GetMasterVol()) + '\n';
		file << std::to_string(m_pcAudioManager->GetMusicVol()) + '\n';
		file << std::to_string(m_pcAudioManager->GetSFXVol()) + '\n';

		// Write out controls
		file << std::to_string(m_bMouseControls) + '\n';
	}
	file.close();
}

CGameLogic::CGameLogic(HWND cWindow)
{
	m_pcComponentManager = new CComponentManager();

	m_pcEntityManager = new CEntityManager(m_pcComponentManager);

	m_pcRenderManager = new CRenderManager(cWindow, m_pcComponentManager);

	m_pcEventManager = new CEventManager(m_pcRenderManager);

	m_pcAudioManager = new CAudioManager();

	m_pcPhysicsManager = new CPhysicsManager(m_pcComponentManager);

	// Create Start Menu
	m_pcRenderManager->AddButtonToMenu(eMenu::START, StartGame, L"Play", 1024, 576, 0.4f, 0.6f, 0.4f, 0.5f);
	m_pcRenderManager->AddButtonToMenu(eMenu::START, StartToOptions, L"Options", 1024, 576, 0.4f, 0.6f, 0.6f, 0.7f);
	m_pcRenderManager->AddButtonToMenu(eMenu::START, ExitGame, L"Quit", 1024, 576, 0.4f, 0.6f, 0.8f, 0.9f);
	m_pcRenderManager->SetTitleToMenu(eMenu::START, L"Thieves Labyrinth", 0.3f, 0.7f, 0.1f, 0.3f);
	// Create Pause Menu
	m_pcRenderManager->AddButtonToMenu(eMenu::PAUSE, TogglePause, L"Resume", 1024, 576, 0.4f, 0.6f, 0.4f, 0.5f);
	m_pcRenderManager->AddButtonToMenu(eMenu::PAUSE, PauseToOptions, L"Options", 1024, 576, 0.4f, 0.6f, 0.6f, 0.7f);
	m_pcRenderManager->AddButtonToMenu(eMenu::PAUSE, GoBackToMain, L"Exit To Main Menu", 1024, 576, 0.4f, 0.6f, 0.8f, 0.9f);
	m_pcRenderManager->SetTitleToMenu(eMenu::PAUSE, L"Pause", 0.3f, 0.7f, 0.1f, 0.3f);
	// Create Win Menu
	m_pcRenderManager->AddButtonToMenu(eMenu::WIN, GoBackToMain, L"Exit To Main Menu", 1024, 576, 0.4f, 0.6f, 0.4f, 0.6f);
	m_pcRenderManager->SetTitleToMenu(eMenu::WIN, L"You Win!!", 0.3f, 0.7f, 0.1f, 0.3f);
	// Create Lose Menu
	m_pcRenderManager->AddButtonToMenu(eMenu::LOSE, GoBackToMain, L"Exit To Main Menu", 1024, 576, 0.4f, 0.6f, 0.4f, 0.6f);
	m_pcRenderManager->SetTitleToMenu(eMenu::LOSE, L"You Lose!!", 0.3f, 0.7f, 0.1f, 0.3f);
	BuildOptionsMenus();

	m_pcLevelManager = new CLevelManager();

	m_pcAIManager = new CAIManager(m_pcComponentManager);

	m_nCurrentState = eGameState::MAIN_MENU;

	m_bStateInitialized = false;
	
	LoadSettings();
}

CGameLogic::~CGameLogic()
{
	delete m_pcAIManager;
	delete m_pcLevelManager;
	delete m_pcRenderManager;
	delete m_pcPhysicsManager;
	delete m_pcAudioManager;
	delete m_pcEventManager;
	delete m_pcEntityManager;
	delete m_pcComponentManager;

	SaveSettings();
}

void CGameLogic::Update()
{
	switch (m_nCurrentState)
	{
	case eGameState::MAIN_MENU:
	{
		m_pcEventManager->Notify();
		m_pcRenderManager->Draw();
		m_cTime->Update();
		break;
	}

	case eGameState::LOADING_LEVEL:
	{

		CPlayerEntity* pPlayer = (CPlayerEntity*)CEntityManager::CreateEntity(eEntity::PLAYER);
		CTransform* pPlayerTransform = (CTransform*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::TRANSFORM);

#pragma region Room Generation

		m_pcLevelManager->CreateLevel();
		
#pragma endregion

#pragma region Player

		pPlayer->m_pcRoom = m_pcLevelManager->m_pcCurrentLevel->m_pcCurrentRoom;

		CEntityManager::AddComponentToEntity(pPlayer, eComponent::RIGIDBODY);
		CCapsuleCollider* pPlayerCollider = (CCapsuleCollider*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::CAPSULE_COLLIDER);
		CMeshRenderer* pPlayerMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::MESH_RENDERER);
		CStats* pPlayerStats = (CStats*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::STATS);
		CAnimatorComponent*	pPlayerAnimator = (CAnimatorComponent*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::ANIMATOR);
		CInventory* pPlayerInventory = (CInventory*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::INVENTORY);
		CLightComponent* pPlayerLight = (CLightComponent*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::LIGHT);
		CFireDemonController* pPlayerController = (CFireDemonController*)CEntityManager::AddComponentToEntity(pPlayer, eComponent::FIRE_DEMON_CONTROLLER);
		pPlayerController->UseMouseControls(m_bMouseControls);

		pPlayerTransform->SetPosition(CLevel::m_pcStartRoom->GetComponent<CTransform>()->GetPosition() - CMath::TVECTOR3(25, 0, 0));
		//pPlayerTransform->SetScale(CMath::TVECTOR3(2.0f, 2.0f, 2.0f));
		
		/*pPlayerCollider->SetCenter(CMath::TVECTOR3(0, 5, 0));
		pPlayerCollider->SetExtent(CMath::TVECTOR3(2, 5, 2));*/

		pPlayerCollider->SetCenter({ 0, 3.5f, 0 });
		pPlayerCollider->SetHeight(7.0f);
		pPlayerCollider->SetRadius(2.0f);

		pPlayerMesh->SetVertexBuffer(eVertexBuffer::FIRE_DEMON);
		pPlayerMesh->SetIndexBuffer(eIndexBuffer::FIRE_DEMON);
		pPlayerMesh->SetTextureCount(1);
		pPlayerMesh->SetTexture(eTexture::FIRE_DEMON_DIFFUSE, 0);
		pPlayerMesh->SetInputLayout(eInputLayout::SKINNED);
		pPlayerMesh->SetVertexShader(eVertexShader::SKINNED);
		pPlayerMesh->SetPixelShader(ePixelShader::DEFAULT);
		pPlayerMesh->SetSampler(eSampler::CLAMP);

		pPlayerStats->SetMaxHP(15.0f);
		pPlayerStats->SetHP(pPlayerStats->GetMaxHP());
		pPlayerStats->SetMaxMP(3.0f);
		pPlayerStats->SetMP(pPlayerStats->GetMaxMP());
		pPlayerStats->SetAttackSpeed(0.5f);
		pPlayerStats->SetMovementSpeed(20.0f);
		pPlayerStats->SetBaseDamage(1.0f);

		pPlayerAnimator->SetAnimator(eAnimator::FIRE_DEMON);
		pPlayerAnimator->SetAnimation(ePlayerAnimation::IDLE);
		pPlayerAnimator->SetAnimationTime(0.0);

		pPlayerLight->SetColor({ 229/255.0f, 137 /255.0f, 39/255.0f, 1 });
		pPlayerLight->SetPosition({0, 4, 0});
		pPlayerLight->SetRadius(50.0f);

		#pragma endregion

#pragma region Camera Creation

		CCameraEntity* pMainCamera = (CCameraEntity*)m_pcEntityManager->CreateEntity(eEntity::CAMERA);
		m_pcEntityManager->AddComponentToEntity(pMainCamera, eComponent::TRANSFORM);
		m_pcEntityManager->AddComponentToEntity(pMainCamera, eComponent::RIGIDBODY);
		m_pcEntityManager->AddComponentToEntity(pMainCamera, eComponent::CAMERA_CONTROLLER);

		CTransform* cameraTransform = pMainCamera->GetComponent<CTransform>();
		cameraTransform->SetPosition(CMath::TVECTOR3(0, 0, 0));

#pragma endregion

		m_nCurrentState = eGameState::PLAYING;
		m_pcRenderManager->ChangeCurrentMenu(eMenu::GAME);
		CGUIManager::NewGame();

		m_cTime->Unpause();

		break;
	}

	case eGameState::PLAYING:
	{

		if (!m_bStateInitialized)
		{
			// TODO Set Music to normal volume
			// TODO Play FootSteps
			// TODO Close pause menu
			m_pcRenderManager->ChangeCurrentMenu(eMenu::GAME);
			PlayButtonSound();
			m_bStateInitialized = true;
		}

		m_pcAIManager->UpdateEnemyBehavior();
		m_pcAIManager->UpdateFlockingBehavior(m_cTime->GetDeltaF());
		m_pcPhysicsManager->Update(m_cTime->GetDeltaF());

		m_pcComponentManager->UpdateControllers();
		m_pcEventManager->Notify();

		m_pcRenderManager->Draw();
		CDebugManager::ClearDebugLines();

		if (CInputManager::GetKeyDown(VK_ESCAPE))
		{
			TogglePause();
		}

		m_pcEntityManager->ProcessDeletionQueue();

		CPlayerEntity* player = (CPlayerEntity*)CEntityManager::GetEntity(0);
		if (player)
		{
			CStats* playerStats = player->GetComponent<CStats>();
			if (playerStats->GetHP() <= 0)
			{
				m_pcRenderManager->ChangeCurrentMenu(eMenu::LOSE);
				m_nCurrentState = eGameState::MAIN_MENU;

			}
			else
			{
				playerStats->SetMP(playerStats->GetMP() + (float)CTime::GetDelta() * 0.1f * playerStats->GetMaxMP());
			}
			if (CLevel::nTotalEnemyCount == 0 || CInputManager::GetKeyDown('O'))
			{
				//do end stuff


				m_pcRenderManager->ChangeCurrentMenu(eMenu::WIN);
				m_nCurrentState = eGameState::PAUSED;

				break;
			}
		}


#ifdef CHEATCODES

		if (CInputManager::GetKeyDown('G'))
		{
			bGodMode = !bGodMode;

		}
		if (CInputManager::GetKeyDown('H'))
		{
			bInfiniteMana = !bInfiniteMana;

		}
		if (CInputManager::GetKeyDown('J'))
		{
			CEntityManager::GetEntity(0)->GetComponent<CStats>()->SetHP(CEntityManager::GetEntity(0)->GetComponent<CStats>()->GetMaxHP());
		}

		if (bGodMode)
		{
			CEntityManager::GetEntity(0)->GetComponent<CStats>()->SetHP(CEntityManager::GetEntity(0)->GetComponent<CStats>()->GetMaxHP());
			CEntityManager::GetEntity(0)->GetComponent<CStats>()->SetMP(CEntityManager::GetEntity(0)->GetComponent<CStats>()->GetMaxMP());
		}
		if (bInfiniteMana)
		{
			CEntityManager::GetEntity(0)->GetComponent<CStats>()->SetMP(CEntityManager::GetEntity(0)->GetComponent<CStats>()->GetMaxMP());
		}

#endif // CHEATCODES

		m_cTime->Update();

		break;
	}

	case eGameState::PAUSED:
	{
		if (!m_bStateInitialized)
		{
			// TODO Set music to play lower
			// TODO Stop Playing Footsteps
			// TODO Open Pause Menu
			ToPause();
			m_bStateInitialized = true;
		}
		m_pcRenderManager->Draw();
		m_pcEventManager->Notify();
		if (CInputManager::GetKeyDown(VK_ESCAPE))
		{
			if (m_pcRenderManager->GetMenuState() == eMenu::PAUSE)
			{
				TogglePause();
			}
			else
			{
				ToPause();
			}
		}

		break;
	}

	case eGameState::QUIT:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}
}

void CGameLogic::BuildOptionsMenus()
{
	// Hand the back buttons to the options menus
	m_pcRenderManager->AddButtonToMenu(eMenu::START_OPTIONS, ToStart, L"Back", 1024, 576, 0.4f, 0.6f, 0.8f, 0.9f);
	m_pcRenderManager->AddButtonToMenu(eMenu::PAUSE_OPTIONS, ToPause, L"Back", 1024, 576, 0.4f, 0.6f, 0.8f, 0.9f);
	m_pcRenderManager->AddButtonToMenu(eMenu::START_OPTIONS, SwapControls, L"", 1024, 576, 0.6f, 0.8f, 0.15f, 0.25f);
	m_pcRenderManager->AddButtonToMenu(eMenu::PAUSE_OPTIONS, SwapControls, L"", 1024, 576, 0.6f, 0.8f, 0.15f, 0.25f);
	// Set the slider stuff for the options menu linked to start
	// MASTER OF VOLUMES I'M PULLING YOUR STRINGS!!
	m_pcRenderManager->AddSliderToMenu(eMenu::START_OPTIONS, eAudio::COUNT, 1024, 576, 0.4f, 0.8f, 0.35f, 0.45f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::START_OPTIONS, L"Master Volume", 0.15f, 0.35f, 0.35f, 0.45f);
	// Please have this off, don't toggle it anymore
	m_pcRenderManager->AddSliderToMenu(eMenu::START_OPTIONS, eAudio::MUSIC, 1024, 576, 0.4f, 0.8f, 0.5f, 0.6f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::START_OPTIONS, L"Music Volume", 0.15f, 0.35f, 0.5f, 0.6f);
	// I honestly don't care what volume you have this at
	m_pcRenderManager->AddSliderToMenu(eMenu::START_OPTIONS, eAudio::SFX, 1024, 576, 0.4f, 0.8f, 0.65f, 0.75f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::START_OPTIONS, L"SFX Volume", 0.15f, 0.35f, 0.65f, 0.75f);
	// GIVE IT A NAME!!
	m_pcRenderManager->SetTitleToMenu(eMenu::START_OPTIONS, L"Options", 0.3f, 0.7f, 0.15f, 0.35f);
	// Second verse, same as the first.  This time for the menu linked to pause
	m_pcRenderManager->AddSliderToMenu(eMenu::PAUSE_OPTIONS, eAudio::COUNT, 1024, 576, 0.4f, 0.8f, 0.35f, 0.45f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::PAUSE_OPTIONS, L"Master Volume", 0.15f, 0.35f, 0.35f, 0.45f);
	m_pcRenderManager->AddSliderToMenu(eMenu::PAUSE_OPTIONS, eAudio::MUSIC, 1024, 576, 0.4f, 0.8f, 0.5f, 0.6f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::PAUSE_OPTIONS, L"Music Volume", 0.15f, 0.35f, 0.5f, 0.6f);
	m_pcRenderManager->AddSliderToMenu(eMenu::PAUSE_OPTIONS, eAudio::SFX, 1024, 576, 0.4f, 0.8f, 0.65f, 0.75f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::PAUSE_OPTIONS, L"SFX Volume", 0.15f, 0.35f, 0.65f, 0.75f);
	m_pcRenderManager->SetTitleToMenu(eMenu::PAUSE_OPTIONS, L"Options", 0.3f, 0.7f, 0.15f, 0.35f);
	// Description text for the buttons for controls
	m_pcRenderManager->AddDescriptionToMenu(eMenu::START_OPTIONS, L"Mouse Controls", 0.6f, 0.8f, 0.15f, 0.25f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::START_OPTIONS, L"Keyboard Controls", 0.6f, 0.8f, 0.15f, 0.25f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::PAUSE_OPTIONS, L"Mouse Controls", 0.6f, 0.8f, 0.15f, 0.25f);
	m_pcRenderManager->AddDescriptionToMenu(eMenu::PAUSE_OPTIONS, L"Keyboard Controls", 0.6f, 0.8f, 0.15f, 0.25f);
}

void CGameLogic::StartGame()
{
	m_nCurrentState = eGameState::LOADING_LEVEL;
	PlayButtonSound();
}

void CGameLogic::ExitGame()
{
	m_nCurrentState = eGameState::QUIT;
	PlayButtonSound();
}

void CGameLogic::TogglePause()
{
	if (m_nCurrentState == eGameState::PLAYING)
	{
		m_nCurrentState = eGameState::PAUSED;
		CTime::Pause();
		m_bStateInitialized = false;
	}

	else if (m_nCurrentState == eGameState::PAUSED)
	{
		m_nCurrentState = eGameState::PLAYING;
		CTime::Unpause();
		m_bStateInitialized = false;
	}
}

void CGameLogic::GoBackToMain()
{

	delete m_pcLevelManager->m_pcCurrentLevel;
	m_pcLevelManager->m_pcCurrentLevel = nullptr;

	m_pcEntityManager->ProcessDeletionQueue();
	m_nCurrentState = eGameState::MAIN_MENU;
	m_pcRenderManager->ChangeCurrentMenu(eMenu::START);
	PlayButtonSound();
}

void CGameLogic::PlayButtonSound()
{
	TAudioMessage playSound = TAudioMessage(true, eAudio::SFX, eSFX::BUTTON);
	CEventManager::SendAudioMessage(playSound);
}

void CGameLogic::StartToOptions()
{
	m_pcRenderManager->ChangeCurrentMenu(eMenu::START_OPTIONS);
	PlayButtonSound();
}

void CGameLogic::PauseToOptions()
{
	m_pcRenderManager->ChangeCurrentMenu(eMenu::PAUSE_OPTIONS);
	PlayButtonSound();
}

void CGameLogic::ToPause()
{
	m_pcRenderManager->ChangeCurrentMenu(eMenu::PAUSE);
	PlayButtonSound();
}

void CGameLogic::ToStart()
{
	m_pcRenderManager->ChangeCurrentMenu(eMenu::START);
	PlayButtonSound();
}

void CGameLogic::SwapControls()
{
	m_bMouseControls = !m_bMouseControls;
	CGUIManager::SetControls(m_bMouseControls);
	if (CEntityManager::GetEntityCount(eEntity::PLAYER) > 0)
	{
		IEntity* player = CEntityManager::GetEntity(0);
		if (player)
		{
			CFireDemonController* flames = player->GetComponent<CFireDemonController>();
			flames->UseMouseControls(m_bMouseControls);
		}
	}
}

#include "LevelManager.h"
#include "EventManager.h"

#include "AnimatorComponent.h"
#include "MeshRenderer.h"
#include "CapsuleCollider.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "Stats.h"
#include "Transform.h"

#include <vector>

CLevel* CLevelManager::m_pcCurrentLevel;
std::vector<CRoomEntity*> CLevelManager::m_pRoomsType;
std::vector<CEnemyEntity*> CLevelManager::m_pcEnemies;
std::vector<CTrapEntity*> CLevelManager::m_pcTraps;

CLevelManager::CLevelManager()
{
	
}

void CLevelManager::CreateLevel()
{
	m_pRoomsType.clear();
	m_pcEnemies.clear();

#pragma region Walls

	CDoorEntity* Door = (CDoorEntity*)CEntityManager::CreateEntity(eEntity::DOOR);
	CEntityManager::AddComponentToEntity(Door, eComponent::TRANSFORM);
	
	CMeshRenderer* pcMeshRender = (CMeshRenderer*)CEntityManager::AddComponentToEntity(Door, eComponent::MESH_RENDERER);
	pcMeshRender->SetVertexBuffer(eVertexBuffer::DOOR);
	pcMeshRender->SetIndexBuffer(eIndexBuffer::DOOR);
	pcMeshRender->SetTextureCount(3);
	pcMeshRender->SetTexture(eTexture::DOOR_DIFFUSE, 0);
	pcMeshRender->SetTexture(eTexture::DOOR_NORMAL, 1);
	pcMeshRender->SetTexture(eTexture::DOOR_SPECULAR, 2);

	pcMeshRender->SetInputLayout(eInputLayout::DEFAULT);
	pcMeshRender->SetVertexShader(eVertexShader::DEFAULT);
	pcMeshRender->SetPixelShader(ePixelShader::SEE_THROUGH);
	pcMeshRender->SetSampler(eSampler::CLAMP);
	
	
	CEntityManager::AddComponentToEntity(Door, eComponent::BOX_COLLIDER);

	CEnvironmentEntity* wall = (CEnvironmentEntity*)CEntityManager::CreateEntity(eEntity::ENVIRONMENT);
	CEntityManager::AddComponentToEntity(wall, eComponent::TRANSFORM);
	CEntityManager::AddComponentToEntity(wall, eComponent::BOX_COLLIDER);

	pcMeshRender = (CMeshRenderer*)CEntityManager::AddComponentToEntity(wall, eComponent::MESH_RENDERER);
	pcMeshRender->SetVertexBuffer(eVertexBuffer::ENVIRONMENT);
	pcMeshRender->SetIndexBuffer(eIndexBuffer::ENVIRONMENT);
	pcMeshRender->SetTextureCount(3);
	pcMeshRender->SetTexture(eTexture::WALL_DIFFUSE, 0);
	pcMeshRender->SetTexture(eTexture::WALL_NORMAL, 1);
	pcMeshRender->SetTexture(eTexture::WALL_SPECULAR, 2);
	pcMeshRender->SetInputLayout(eInputLayout::DEFAULT);
	pcMeshRender->SetVertexShader(eVertexShader::DEFAULT);
	pcMeshRender->SetPixelShader(ePixelShader::SEE_THROUGH);
	pcMeshRender->SetSampler(eSampler::CLAMP);
	

	// Pillar
	CEnvironmentEntity* Pillar = (CEnvironmentEntity*)CEntityManager::CreateEntity(eEntity::ENVIRONMENT);
	CEntityManager::AddComponentToEntity(Pillar, eComponent::TRANSFORM);
	CEntityManager::AddComponentToEntity(Pillar, eComponent::BOX_COLLIDER);

	pcMeshRender = (CMeshRenderer*)CEntityManager::AddComponentToEntity(Pillar, eComponent::MESH_RENDERER);
	pcMeshRender->SetVertexBuffer(eVertexBuffer::PILLAR);
	pcMeshRender->SetIndexBuffer(eIndexBuffer::PILLAR);
	pcMeshRender->SetTextureCount(3);
	pcMeshRender->SetTexture(eTexture::PILLAR_DIFFUSE, 0);
	pcMeshRender->SetTexture(eTexture::PILLAR_NORMAL, 1);
	pcMeshRender->SetTexture(eTexture::PILLAR_SPECULAR, 2);
	pcMeshRender->SetInputLayout(eInputLayout::DEFAULT);
	pcMeshRender->SetVertexShader(eVertexShader::DEFAULT);
	pcMeshRender->SetPixelShader(ePixelShader::SEE_THROUGH);
	pcMeshRender->SetSampler(eSampler::CLAMP);
	

	wall->SetActiveState(false);
	Door->SetActiveState(false);
	Pillar->SetActiveState(false);

#pragma endregion

#pragma region Enemies

	// Mage
	CEnemyEntity* pcMage = (CEnemyEntity*)CEntityManager::CreateEntity(eEntity::ENEMY);
	CEntityManager::AddComponentToEntity(pcMage, eComponent::TRANSFORM);
	CEntityManager::AddComponentToEntity(pcMage, eComponent::RIGIDBODY);


	CCapsuleCollider* pcMageCollider = (CCapsuleCollider*)CEntityManager::AddComponentToEntity(pcMage, eComponent::CAPSULE_COLLIDER);
	pcMageCollider->SetCenter(CMath::TVECTOR3(0, 3.5f, 0));
	pcMageCollider->SetHeight(7.0f);
	pcMageCollider->SetRadius(1.0f);

	CMeshRenderer* pcMageMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcMage, eComponent::MESH_RENDERER);
	pcMageMesh->SetVertexBuffer(eVertexBuffer::ENEMY_MAGE);
	pcMageMesh->SetIndexBuffer(eIndexBuffer::ENEMY_MAGE);
	pcMageMesh->SetTextureCount(1);
	pcMageMesh->SetTexture(eTexture::ENEMY_MAGE_DIFFUSE, 0);
	pcMageMesh->SetInputLayout(eInputLayout::SKINNED);
	pcMageMesh->SetVertexShader(eVertexShader::SKINNED);
	pcMageMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcMageMesh->SetSampler(eSampler::CLAMP);

	CAnimatorComponent* pcMageAnimator = (CAnimatorComponent*)CEntityManager::AddComponentToEntity(pcMage, eComponent::ANIMATOR);
	pcMageAnimator->SetAnimator(eAnimator::MAGE);
	pcMageAnimator->SetAnimation(eEnemyAnimation::IDLE);
	pcMageAnimator->SetAnimationTime(0.0);

	CStats*	pcMageStats = (CStats*)CEntityManager::AddComponentToEntity(pcMage, eComponent::STATS);
	pcMageStats->SetMaxHP(2.0f);
	pcMageStats->SetHP(pcMageStats->GetMaxHP());
	pcMageStats->SetMaxMP(1000.0f);
	pcMageStats->SetMP(pcMageStats->GetMaxMP());
	pcMageStats->SetMovementSpeed(8.0f);
	pcMageStats->SetBaseDamage(1.0f);

	CEntityManager::AddComponentToEntity(pcMage, eComponent::MAGE_CONTROLLER);

	pcMage->SetActiveState(false);
	m_pcEnemies.push_back(pcMage);

	// Chicken
	CEnemyEntity* pcChicken = (CEnemyEntity*)CEntityManager::CreateEntity(eEntity::ENEMY);
	CEntityManager::AddComponentToEntity(pcChicken, eComponent::TRANSFORM);
	CEntityManager::AddComponentToEntity(pcChicken, eComponent::RIGIDBODY);


	CCapsuleCollider* pcChickenCollider = (CCapsuleCollider*)CEntityManager::AddComponentToEntity(pcChicken, eComponent::CAPSULE_COLLIDER);
	pcChickenCollider->SetCenter(CMath::TVECTOR3(0, 1.5f, 0));
	pcChickenCollider->SetHeight(3.0f);
	pcChickenCollider->SetRadius(1.0f);

	CMeshRenderer* pcChickenMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcChicken, eComponent::MESH_RENDERER);
	pcChickenMesh->SetVertexBuffer(eVertexBuffer::ENEMY_CHICKEN);
	pcChickenMesh->SetIndexBuffer(eIndexBuffer::ENEMY_CHICKEN);
	pcChickenMesh->SetTextureCount(1);
	pcChickenMesh->SetTexture(eTexture::ENEMY_CHICKEN_DIFFUSE, 0);
	pcChickenMesh->SetInputLayout(eInputLayout::DEFAULT);
	pcChickenMesh->SetVertexShader(eVertexShader::DEFAULT);
	pcChickenMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcChickenMesh->SetSampler(eSampler::WRAP);

	/*CAnimatorComponent* pcChickenAnimator = (CAnimatorComponent*)CEntityManager::AddComponentToEntity(pcChicken, eComponent::ANIMATOR);
	pcChickenAnimator->SetAnimator(eAnimator::MAGE);
	pcChickenAnimator->SetAnimation(eEnemyAnimation::IDLE);
	pcChickenAnimator->SetAnimationTime(0.0);*/

	CStats*	pcChickenStats = (CStats*)CEntityManager::AddComponentToEntity(pcChicken, eComponent::STATS);
	pcChickenStats->SetMaxHP(1.0f);
	pcChickenStats->SetHP(pcChickenStats->GetMaxHP());
	pcChickenStats->SetMaxMP(0.0f);
	pcChickenStats->SetMP(pcChickenStats->GetMaxMP());
	pcChickenStats->SetMovementSpeed(15.0f);
	pcChickenStats->SetBaseDamage(3.0f);

	CEntityManager::AddComponentToEntity(pcChicken, eComponent::CHICKEN_CONTROLLER);

	pcChicken->SetActiveState(false);
	m_pcEnemies.push_back(pcChicken);

	// Viking
	CEnemyEntity* pcViking = (CEnemyEntity*)CEntityManager::CreateEntity(eEntity::ENEMY);
	CEntityManager::AddComponentToEntity(pcViking, eComponent::TRANSFORM);
	pcViking->GetComponent<CTransform>()->SetScale({ 3.25f, 3.25f, 3.25f });
	CEntityManager::AddComponentToEntity(pcViking, eComponent::RIGIDBODY);


	CCapsuleCollider* pcVikingCollider = (CCapsuleCollider*)CEntityManager::AddComponentToEntity(pcViking, eComponent::CAPSULE_COLLIDER);
	pcVikingCollider->SetCenter(CMath::TVECTOR3(0, 3.5f, 0));
	pcVikingCollider->SetHeight(2.0f);
	pcVikingCollider->SetRadius(0.5f);

	CMeshRenderer* pcVikingMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcViking, eComponent::MESH_RENDERER);
	pcVikingMesh->SetVertexBuffer(eVertexBuffer::ENEMY_VIKING);
	pcVikingMesh->SetIndexBuffer(eIndexBuffer::ENEMY_VIKING);
	pcVikingMesh->SetTextureCount(1);
	pcVikingMesh->SetTexture(eTexture::ENEMY_VIKING_DIFFUSE, 0);
	pcVikingMesh->SetInputLayout(eInputLayout::SKINNED);
	pcVikingMesh->SetVertexShader(eVertexShader::SKINNED);
	pcVikingMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcVikingMesh->SetSampler(eSampler::CLAMP);

	CAnimatorComponent* pcVikingAnimator = (CAnimatorComponent*)CEntityManager::AddComponentToEntity(pcViking, eComponent::ANIMATOR);
	pcVikingAnimator->SetAnimator(eAnimator::VIKING);
	pcVikingAnimator->SetAnimation(eEnemyAnimation::IDLE);
	pcVikingAnimator->SetAnimationTime(0.0);

	CStats*	pcVikingStats = (CStats*)CEntityManager::AddComponentToEntity(pcViking, eComponent::STATS);
	pcVikingStats->SetMaxHP(4.0f);
	pcVikingStats->SetHP(4.0f);
	pcVikingStats->SetMaxMP(0.0f);
	pcVikingStats->SetMP(0.0f);
	pcVikingStats->SetMovementSpeed(10.0f);
	pcVikingStats->SetBaseDamage(1.0f);
	pcVikingStats->SetAttackSpeed(1.0f);

	CEntityManager::AddComponentToEntity(pcViking, eComponent::VIKING_CONTROLLER);

	pcViking->SetActiveState(false);
	m_pcEnemies.push_back(pcViking);


#pragma endregion

#pragma region Room 1 

	CRoomEntity* pcRoom = (CRoomEntity*)CEntityManager::CreateEntity(eEntity::ROOM);
	CEntityManager::AddComponentToEntity(pcRoom, eComponent::TRANSFORM);
	CMeshRenderer* pcMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcRoom, eComponent::MESH_RENDERER);
	pcMesh->SetVertexBuffer(eVertexBuffer::ROOM1);
	pcMesh->SetIndexBuffer(eIndexBuffer::ROOM1);
	pcMesh->SetTextureCount(3);
	pcMesh->SetTexture(eTexture::FLOOR_DIFFUSE, 0);
	pcMesh->SetTexture(eTexture::FLOOR_NORMAL, 1);
	pcMesh->SetTexture(eTexture::FLOOR_SPECULAR, 2);
	pcMesh->SetInputLayout(eInputLayout::DEFAULT);
	pcMesh->SetVertexShader(eVertexShader::DEFAULT);
	pcMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcMesh->SetSampler(eSampler::WRAP);

	//Pillars
	for (int i = 0; i < 4; i++)
	{
		pcRoom->m_pcPillars.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(Pillar));
		pcRoom->m_pcPillars[i]->m_pcRoom = pcRoom;
	}
	pcRoom->m_pcPillars[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47, 0, 47));
	pcRoom->m_pcPillars[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47, 0, -47));
	pcRoom->m_pcPillars[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-47, 0, 47));
	pcRoom->m_pcPillars[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-47, 0, -47));
	
	for (int i = 0; i < 4; i++)
	{
		pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0,7.5,0));
		pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(4, 5, 5));
	}

	//Walls
	for (int i = 0; i < 8; i++)
	{
		pcRoom->m_pcWalls.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(wall));
		pcRoom->m_pcWalls[i]->m_pcRoom = pcRoom;
	}
	pcRoom->m_pcWalls[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(27.5f, -6.0f, 50.0f));
	pcRoom->m_pcWalls[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-25.5f, -6.0f, 51.0f));
	pcRoom->m_pcWalls[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(23.0f, -6.0f, -47.5f));
	pcRoom->m_pcWalls[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29.0f, -6.0f, -47.5f));
	pcRoom->m_pcWalls[4]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-50.5f, -6.0f, 27.0f));
	pcRoom->m_pcWalls[5]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47.5f, -6.0f, -29.0f));
	pcRoom->m_pcWalls[6]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47.5f, -6.0f, 23.5f));
	pcRoom->m_pcWalls[7]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-50.5f, -6.0f, -23.0f));

	//Rotate Walls
	CMath::TVECTOR4 Rotation90 = CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 90);
	CMath::TVECTOR4 Rotation90N = CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, -90);
	CMath::TVECTOR4 Rotation0 = CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 0);
	CMath::TVECTOR4 Rotation180 = CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 180);

	for (int i = 0; i < 4; i++)
	{
		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(Rotation90);
	}
	for (int i = 4; i < 8; i++)
	{
		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(Rotation0);
	}

	for (int i = 0; i < pcRoom->m_pcWalls.size(); i++)
	{
		pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, -2));
		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetScale({ 1.3f, 1, 1.3f });
	}
	pcRoom->m_pcWalls[6]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, 2));
	pcRoom->m_pcWalls[5]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, 2));

	//SetExtent
	pcRoom->m_pcWalls[0]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 15.5));
	pcRoom->m_pcWalls[1]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[2]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 14.5));
	pcRoom->m_pcWalls[3]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 14.5));
	pcRoom->m_pcWalls[4]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[5]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[6]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[7]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));

	//Doors
	for (int i = 0; i < 4; i++)
	{
		pcRoom->m_pcDoors.push_back((CDoorEntity*)CEntityManager::CloneEntity(Door));
		pcRoom->m_pcDoors[i]->m_pcRoom = pcRoom;
	}
	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(48.5, 0, 0));
	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-48.5, 0, 0));
	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, 48.5));
	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, -48.5));

	//Rotate
	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetRotation(Rotation0);
	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetRotation(Rotation90);
	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetRotation(Rotation90N);
	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetRotation(Rotation180);

	for (size_t i = 0; i < 4; i++)
	{
		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 9, -0.7f });
		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(0.2f, 6, 9));
	}

	//Enemies
	pcRoom->SetActiveState(false);
	m_pRoomsType.push_back(pcRoom);
	

	//Light
	//CLightEntity* pcLight = (CLightEntity*)CEntityManager::CreateEntity(eEntity::LIGHT);
	//pcLight->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	//pcLight->SetRadius(10.0f);

	//CEntityManager::AddComponentToEntity(pcLight, eComponent::TRANSFORM);

	#pragma endregion

#pragma region Room 2
	//pcRoom = nullptr;
//	pcRoom = (CRoomEntity*)CEntityManager::CreateEntity(eEntity::ROOM);
//	CEntityManager::AddComponentToEntity(pcRoom, eComponent::TRANSFORM);
//	pcMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcRoom, eComponent::MESH_RENDERER);
//	pcMesh->SetVertexBuffer(eVertexBuffer::ROOM2);
//	pcMesh->SetIndexBuffer(eIndexBuffer::ROOM2);
//	pcMesh->SetTextureCount(1);
//	pcMesh->SetTexture(eTexture::ROOM2, 0);
//	pcMesh->SetInputLayout(eInputLayout::DEFAULT);
//	pcMesh->SetVertexShader(eVertexShader::DEFAULT);
//	pcMesh->SetPixelShader(ePixelShader::DEFAULT);
//	pcMesh->SetSampler(eSampler::WRAP);
//
//	//Walls
//	for (int i = 0; i < 16; i++)
//	{
//		pcRoom->m_pcWalls.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(wall));
//		
//
//		pcRoom->m_pcWalls[i]->m_pcRoom = pcRoom;
//	}
//	pcRoom->m_pcWalls[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(19, 0, 29));
//	pcRoom->m_pcWalls[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-19, 0, 29));
//	pcRoom->m_pcWalls[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(19, 0, -29));
//	pcRoom->m_pcWalls[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-19, 0, -29));
//	pcRoom->m_pcWalls[4]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(29, 0, 19));
//	pcRoom->m_pcWalls[5]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29, 0, 19));
//	pcRoom->m_pcWalls[6]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(29, 0, -19));
//	pcRoom->m_pcWalls[7]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29, 0, -19));
//	pcRoom->m_pcWalls[8]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(10, 0, 40));
//	pcRoom->m_pcWalls[9]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-10, 0, 40));
//	pcRoom->m_pcWalls[10]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(10, 0, -40));
//	pcRoom->m_pcWalls[11]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-10, 0, -40));
//	pcRoom->m_pcWalls[12]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(40, 0, 10));
//	pcRoom->m_pcWalls[13]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-40, 0, 10));
//	pcRoom->m_pcWalls[14]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(40, 0, -10));
//	pcRoom->m_pcWalls[15]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-40, 0, -10));
//
//	//Rotate Walls
//	for (int i = 0; i <= 3; i++)
//	{
//		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 90.0f));
//	}
//
//	for (int i = 12; i <= 15; i++)
//	{
//		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 90.0f));
//	}
//
//	int wallsize = (int)pcRoom->m_pcWalls.size();
//	for (int i = 0; i < wallsize; i++)
//	{
//		pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 0, 0 });
//		pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 12, 10));
//	}
//
//	//Doors
//	for (int i = 0; i < 4; i++)
//	{
//		pcRoom->m_pcDoors.push_back((CDoorEntity*)CEntityManager::CloneEntity(Door));
//
//		pcRoom->m_pcDoors[i]->m_pcRoom = pcRoom;
//	}
//	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(49, 0, 0));
//	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-49, 0, 0));
//	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, 49));
//	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, -49));
//
//	//Rotate
//	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, -90));
//	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 90));
//	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 180));
//	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 0));
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 0, 0 });
//		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(0.5f, 12, 10));
//
//
//	}
//
//	//Enemies
//	for (int i = 0; i < 1; i++)
//	{
//		pcRoom->m_pcEnemies.push_back((CEnemyEntity*)CEntityManager::CloneEntity(pcEnemy));
//		pcRoom->m_pcEnemies[i]->m_pcRoom = pcRoom;
//	}
//	pcRoom->m_nEnemyCount = (int)pcRoom->m_pcEnemies.size();
//	pcRoom->m_pcEnemies[0]->GetComponent<CTransform>()->SetPosition({ 20, 0, 10 });
//
//	m_pRoomsType.push_back(pcRoom);
//
//	pcRoom->SetActiveState(false);
//
//#pragma endregion
//
//#pragma region Room 3
//
//	pcRoom = (CRoomEntity*)CEntityManager::CreateEntity(eEntity::ROOM);
//	CEntityManager::AddComponentToEntity(pcRoom, eComponent::TRANSFORM);
//	pcMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcRoom, eComponent::MESH_RENDERER);
//	pcMesh->SetVertexBuffer(eVertexBuffer::ROOM3);
//	pcMesh->SetIndexBuffer(eIndexBuffer::ROOM3);
//	pcMesh->SetTextureCount(1);
//	pcMesh->SetTexture(eTexture::ROOM3, 0);
//	pcMesh->SetInputLayout(eInputLayout::DEFAULT);
//	pcMesh->SetVertexShader(eVertexShader::DEFAULT);
//	pcMesh->SetPixelShader(ePixelShader::DEFAULT);
//	pcMesh->SetSampler(eSampler::WRAP);
//
//	//Walls
//	for (int i = 0; i < 9; i++)
//	{
//		pcRoom->m_pcWalls.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(wall));
//		CEntityManager::AddComponentToEntity(pcRoom->m_pcWalls[i], eComponent::TRANSFORM);
//		CEntityManager::AddComponentToEntity(pcRoom->m_pcWalls[i], eComponent::BOX_COLLIDER);
//
//		pcRoom->m_pcWalls[i]->m_pcRoom = pcRoom;
//	}
//	pcRoom->m_pcWalls[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(49, 0, 29));
//	pcRoom->m_pcWalls[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(29, 0, 49));
//	pcRoom->m_pcWalls[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(49, 0, -29));
//	pcRoom->m_pcWalls[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(29, 0, -49));
//	pcRoom->m_pcWalls[4]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-49, 0, 29));
//	pcRoom->m_pcWalls[5]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29, 0, 49));
//	pcRoom->m_pcWalls[6]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-49, 0, -29));
//	pcRoom->m_pcWalls[7]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29, 0, -49));
//	pcRoom->m_pcWalls[8]->GetComponent<CTransform>()->SetPosition(pcRoom->GetComponent<CTransform>()->GetPosition());
//
//	//Rotate Walls
//	for (int i = 0; i < 8; i++)
//	{
//		if (i % 2 == 0)
//		{
//			pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 0));
//		}
//		else
//		{
//			pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 90.0f));
//		}
//	}
//
//	wallsize = (int)pcRoom->m_pcWalls.size();
//	for (size_t i = 0; i < wallsize - 1; i++)
//	{
//		pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 0, 0 });
//		pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 12, 20));
//	}
//	pcRoom->m_pcWalls[8]->GetComponent<CBoxCollider>()->SetCenter({ 0, 0, 0 });
//	pcRoom->m_pcWalls[8]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(16, 6, 15.5));
//
//	//Doors
//	for (int i = 0; i < 4; i++)
//	{
//		pcRoom->m_pcDoors.push_back((CDoorEntity*)CEntityManager::CloneEntity(Door));
//
//		pcRoom->m_pcDoors[i]->m_pcRoom = pcRoom;
//	}
//	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(49, 0, 0));
//	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-49, 0, 0));
//	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, 49));
//	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, -49));
//
//	//Rotate
//	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, -90));
//	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 90));
//	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 180));
//	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetRotation(CMath::QuaternionFromAxisAngle({ 0, 1, 0 }, 0));
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 0, 0 });
//		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(0.5f, 12, 10));
//
//
//	}
//
//	//Enemies
//	for (int i = 0; i < 1; i++)
//	{
//		pcRoom->m_pcEnemies.push_back((CEnemyEntity*)CEntityManager::CloneEntity(pcEnemy));
//		pcRoom->m_pcEnemies[i]->m_pcRoom = pcRoom;
//	}
//	pcRoom->m_nEnemyCount = (int)pcRoom->m_pcEnemies.size();
//	pcRoom->m_pcEnemies[0]->GetComponent<CTransform>()->SetPosition({ 20, 0, 10 });
//
//	m_pRoomsType.push_back(pcRoom);
//
//	pcRoom->SetActiveState(false);

#pragma endregion

#pragma region Room 3
pcRoom = (CRoomEntity*)CEntityManager::CreateEntity(eEntity::ROOM);
CEntityManager::AddComponentToEntity(pcRoom, eComponent::TRANSFORM);
pcMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcRoom, eComponent::MESH_RENDERER);
pcMesh->SetVertexBuffer(eVertexBuffer::ROOM3);
pcMesh->SetIndexBuffer(eIndexBuffer::ROOM3);
pcMesh->SetTextureCount(3);
pcMesh->SetTexture(eTexture::FLOOR_DIFFUSE, 0);
pcMesh->SetTexture(eTexture::FLOOR_NORMAL, 1);
pcMesh->SetTexture(eTexture::FLOOR_SPECULAR, 2);
pcMesh->SetInputLayout(eInputLayout::DEFAULT);
pcMesh->SetVertexShader(eVertexShader::DEFAULT);
pcMesh->SetPixelShader(ePixelShader::DEFAULT);
pcMesh->SetSampler(eSampler::WRAP);

//Pillars
for (int i = 0; i < 5; i++)
{
	pcRoom->m_pcPillars.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(Pillar));
	pcRoom->m_pcPillars[i]->m_pcRoom = pcRoom;
}
pcRoom->m_pcPillars[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47, 0, 47));
pcRoom->m_pcPillars[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47, 0, -47));
pcRoom->m_pcPillars[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-47, 0, 47));
pcRoom->m_pcPillars[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-47, 0, -47));
pcRoom->m_pcPillars[4]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, -1.5, 0));
pcRoom->m_pcPillars[4]->GetComponent<CTransform>()->SetScale(CMath::TVECTOR3(3, 3, 3));

for (int i = 0; i < 5; i++)
{
	pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 7.5, 0));
	pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(5, 5, 5));
}

//Walls
for (int i = 0; i < 8; i++)
{
	pcRoom->m_pcWalls.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(wall));
	pcRoom->m_pcWalls[i]->m_pcRoom = pcRoom;
}
pcRoom->m_pcWalls[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(27.5f, -6.0f, 50.0f));
pcRoom->m_pcWalls[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-25.5f, -6.0f, 51.0f));
pcRoom->m_pcWalls[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(23.0f, -6.0f, -47.5f));
pcRoom->m_pcWalls[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29.0f, -6.0f, -47.5f));
pcRoom->m_pcWalls[4]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-50.5f, -6.0f, 27.0f));
pcRoom->m_pcWalls[5]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47.5f, -6.0f, -29.0f));
pcRoom->m_pcWalls[6]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47.5f, -6.0f, 23.5f));
pcRoom->m_pcWalls[7]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-50.5f, -6.0f, -23.0f));


//Rotate Walls

for (int i = 0; i < 4; i++)
{
	pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(Rotation90);
}
for (int i = 4; i < 8; i++)
{
	pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(Rotation0);
}

for (int i = 0; i <= 7; i++)
{
	pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, -2));
	pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetScale({ 1.3f, 1.0f, 1.3f });
	
}
pcRoom->m_pcWalls[6]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, 2));
pcRoom->m_pcWalls[5]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, 2));



//SetExtent
pcRoom->m_pcWalls[0]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 15.5));
pcRoom->m_pcWalls[1]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
pcRoom->m_pcWalls[2]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 14.5));
pcRoom->m_pcWalls[3]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 14.5));
pcRoom->m_pcWalls[4]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
pcRoom->m_pcWalls[5]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
pcRoom->m_pcWalls[6]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
pcRoom->m_pcWalls[7]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));


//Doors
for (int i = 0; i < 4; i++)
{
	pcRoom->m_pcDoors.push_back((CDoorEntity*)CEntityManager::CloneEntity(Door));
	pcRoom->m_pcDoors[i]->m_pcRoom = pcRoom;
}
pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(48.5, 0, 0));
pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-48.5, 0, 0));
pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, 48.5));
pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, -48.5));

//Rotate
pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetRotation(Rotation0);
pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetRotation(Rotation90);
pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetRotation(Rotation90N);
pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetRotation(Rotation180);

for (size_t i = 0; i < 4; i++)
{
	pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 9, -0.7f });
	pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(0.2f, 6, 9));
}

//Enemies

pcRoom->SetActiveState(false);
m_pRoomsType.push_back(pcRoom);
	

#pragma endregion

#pragma region Room 4

	pcRoom = (CRoomEntity*)CEntityManager::CreateEntity(eEntity::ROOM);
	CEntityManager::AddComponentToEntity(pcRoom, eComponent::TRANSFORM);
	pcMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcRoom, eComponent::MESH_RENDERER);
	pcMesh->SetVertexBuffer(eVertexBuffer::ROOM1);
	pcMesh->SetIndexBuffer(eIndexBuffer::ROOM1);
	pcMesh->SetTextureCount(3);
	pcMesh->SetTexture(eTexture::FLOOR_DIFFUSE, 0);
	pcMesh->SetTexture(eTexture::FLOOR_NORMAL, 1);
	pcMesh->SetTexture(eTexture::FLOOR_SPECULAR, 2);
	pcMesh->SetInputLayout(eInputLayout::DEFAULT);
	pcMesh->SetVertexShader(eVertexShader::DEFAULT);
	pcMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcMesh->SetSampler(eSampler::WRAP);
	
	//Pillars
	for (int i = 0; i < 8; i++)
	{
		pcRoom->m_pcPillars.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(Pillar));
		pcRoom->m_pcPillars[i]->m_pcRoom = pcRoom;
		pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 7.5, 0 });
		pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetExtent({ 4, 5, 5 });
	}
	pcRoom->m_pcPillars[0]->GetComponent<CTransform>()->SetPosition({ 47, 0, 47 });
	pcRoom->m_pcPillars[1]->GetComponent<CTransform>()->SetPosition({ 47, 0, -47 });
	pcRoom->m_pcPillars[2]->GetComponent<CTransform>()->SetPosition({ -47, 0, 47 });
	pcRoom->m_pcPillars[3]->GetComponent<CTransform>()->SetPosition({ -47, 0, -47 });
	pcRoom->m_pcPillars[4]->GetComponent<CTransform>()->SetPosition({ 25, 0, 25 });
	pcRoom->m_pcPillars[5]->GetComponent<CTransform>()->SetPosition({ 25, 0, -25 });
	pcRoom->m_pcPillars[6]->GetComponent<CTransform>()->SetPosition({ -25, 0, 25 });
	pcRoom->m_pcPillars[7]->GetComponent<CTransform>()->SetPosition({ -25, 0, -25 });
	
	for (int i = 4; i < 8; i++)
	{
		pcRoom->m_pcPillars[i]->GetComponent<CTransform>()->SetScale({ 0.75f, 1.0f, 0.75f });
		pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 7.5, 0 });
		pcRoom->m_pcPillars[i]->GetComponent<CBoxCollider>()->SetExtent({ 4, 5, 5 });
	}
	
	//Walls
	for (int i = 0; i < 8; i++)
	{
		pcRoom->m_pcWalls.push_back((CEnvironmentEntity*)CEntityManager::CloneEntity(wall));
		pcRoom->m_pcWalls[i]->m_pcRoom = pcRoom;
	}
	pcRoom->m_pcWalls[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(27.5f, -6.0f, 50.0f));
	pcRoom->m_pcWalls[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-25.5f, -6.0f, 51.0f));
	pcRoom->m_pcWalls[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(23.0f, -6.0f, -47.5f));
	pcRoom->m_pcWalls[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-29.0f, -6.0f, -47.5f));
	pcRoom->m_pcWalls[4]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-50.5f, -6.0f, 27.0f));
	pcRoom->m_pcWalls[5]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47.5f, -6.0f, -29.0f));
	pcRoom->m_pcWalls[6]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(47.5f, -6.0f, 23.5f));
	pcRoom->m_pcWalls[7]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-50.5f, -6.0f, -23.0f));
	
	//Rotate Walls	
	for (int i = 0; i < 4; i++)
	{
		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(Rotation90);
	}
	for (int i = 4; i < 8; i++)
	{
		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetRotation(Rotation0);
	}
	
	for (int i = 0; i < pcRoom->m_pcWalls.size(); i++)
	{
		pcRoom->m_pcWalls[i]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, -2));
		pcRoom->m_pcWalls[i]->GetComponent<CTransform>()->SetScale({ 1.3f, 1, 1.3f });
	}
	pcRoom->m_pcWalls[6]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, 2));
	pcRoom->m_pcWalls[5]->GetComponent<CBoxCollider>()->SetCenter(CMath::TVECTOR3(0, 10, 2));
	
	//SetExtent
	pcRoom->m_pcWalls[0]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 15.5));
	pcRoom->m_pcWalls[1]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[2]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 14.5));
	pcRoom->m_pcWalls[3]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 14.5));
	pcRoom->m_pcWalls[4]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[5]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[6]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	pcRoom->m_pcWalls[7]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(1, 8, 13.5));
	
	//Doors
	for (int i = 0; i < 4; i++)
	{
		pcRoom->m_pcDoors.push_back((CDoorEntity*)CEntityManager::CloneEntity(Door));
		pcRoom->m_pcDoors[i]->m_pcRoom = pcRoom;
	}
	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(48.5, 0, 0));
	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(-48.5, 0, 0));
	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, 48.5));
	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetPosition(CMath::TVECTOR3(0, 0, -48.5));
	
	//Rotate
	pcRoom->m_pcDoors[1]->GetComponent<CTransform>()->SetRotation(Rotation0);
	pcRoom->m_pcDoors[2]->GetComponent<CTransform>()->SetRotation(Rotation90);
	pcRoom->m_pcDoors[3]->GetComponent<CTransform>()->SetRotation(Rotation90N);
	pcRoom->m_pcDoors[0]->GetComponent<CTransform>()->SetRotation(Rotation180);
	
	for (size_t i = 0; i < 4; i++)
	{
		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetCenter({ 0, 9, -0.7f });
		pcRoom->m_pcDoors[i]->GetComponent<CBoxCollider>()->SetExtent(CMath::TVECTOR3(0.2f, 6, 9));
	}
	
	//Enemies
	pcRoom->SetActiveState(false);
	m_pRoomsType.push_back(pcRoom);
	
	
	//Light
	//CLightEntity* pcLight = (CLightEntity*)CEntityManager::CreateEntity(eEntity::LIGHT);
	//pcLight->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	//pcLight->SetRadius(10.0f);
	
	//CEntityManager::AddComponentToEntity(pcLight, eComponent::TRANSFORM);

#pragma endregion


#pragma region Traps

	CTrapEntity* pcSpikes = (CTrapEntity*)CEntityManager::CreateEntity(eEntity::TRAP);
	CTransform* pcSpikeTransform = (CTransform*)CEntityManager::AddComponentToEntity(pcSpikes, eComponent::TRANSFORM);

	CBoxCollider* pcSpikeCollider = (CBoxCollider*)CEntityManager::AddComponentToEntity(pcSpikes, eComponent::BOX_COLLIDER);
	pcSpikeCollider->SetCenter({ 0, 3.0f, 0 });
	pcSpikeCollider->SetExtent({ 5, 5.0f, 5 });
	pcSpikeCollider->SetTrigger(true);


	CMeshRenderer* pcSpikeMesh = (CMeshRenderer*)CEntityManager::AddComponentToEntity(pcSpikes, eComponent::MESH_RENDERER);
	pcSpikeMesh->SetVertexBuffer(eVertexBuffer::SPIKE_TRAP);
	pcSpikeMesh->SetIndexBuffer(eIndexBuffer::SPIKE_TRAP);
	pcSpikeMesh->SetTextureCount(1);
	pcSpikeMesh->SetTexture(eTexture::SPIKE_TRAP_DIFFUSE, 0);
	pcSpikeMesh->SetInputLayout(eInputLayout::DEFAULT);
	pcSpikeMesh->SetVertexShader(eVertexShader::DEFAULT);
	pcSpikeMesh->SetPixelShader(ePixelShader::DEFAULT);
	pcSpikeMesh->SetSampler(eSampler::CLAMP);


	CEntityManager::AddComponentToEntity(pcSpikes, eComponent::SPIKE_TRAP_COMPONENT);
	m_pcTraps.push_back(pcSpikes);
#pragma endregion

	m_pcCurrentLevel = new CLevel();

	m_pcCurrentLevel->RandomizeRoomEnemies(m_pcEnemies);

	pcSpikeTransform->SetPosition(CLevelManager::m_pcCurrentLevel->m_pcCurrentRoom->GetComponent<CTransform>()->GetPosition()
		+ CMath::TVECTOR3(-25, .2f, 5));
	pcSpikeTransform->SetScale({ 0.5f, 0.5f, 0.5f });
	pcSpikes->m_pcRoom = m_pcCurrentLevel->m_pcCurrentRoom;
}

CLevelManager::~CLevelManager()
{
	if (m_pcCurrentLevel)	delete m_pcCurrentLevel;
}

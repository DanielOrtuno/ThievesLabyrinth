#pragma once
#include "Level.h"

class CLevelManager
{
private:

public:
	static CLevel* m_pcCurrentLevel;

	static std::vector<CRoomEntity*> m_pRoomsType;
	static std::vector<CEnemyEntity*> m_pcEnemies;
	static std::vector<CTrapEntity*> m_pcTraps;

	void CreateLevel();

	CLevelManager();
	~CLevelManager();
};


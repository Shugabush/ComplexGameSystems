#pragma once

#include "Enemy.h"

#include <vector>
#include <queue>

class EnemyManager
{
	std::queue<Enemy*> PendingEnemies;
	std::vector<Enemy*> Enemies;
	std::queue<Enemy*> DestroyedEnemies;

	bool UpdateTerminated;

public:
	void Update();
	void Draw();

	bool ShouldUpdate = true;

	void SpawnEnemy(Enemy* enemy);
	void DestroyEnemy(Enemy* enemy);
};
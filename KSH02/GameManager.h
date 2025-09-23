#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"
enum class TileState
{

	Road = 0,
	Wall = 1,
	SoftRock = 10,
	UnbreakableRock = 100,
	Bomb = 20,
	HitBombEffect =21,
	NotHitBombEffect =22,
	Player=50,
	Enemy=60
};

class GameManager
{
public:
	Player* player = new Player();
	void InitializeMap();
	void PrintMap();
	void Clear();
	void StagePlay();

	bool isClear();
	bool isHit();
	static const int MapSize = 10;
	int Map[MapSize][MapSize];
};


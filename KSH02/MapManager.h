#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"

enum class MTileState
{

	Road = 0,
	Wall = 1,
	SoftRock = 10,
	UnbreakableRock = 100,
	Bomb = 20,
	HitBombEffect = 21,
	NotHitBombEffect = 22,
	Player = 50,
	Enemy = 60
};
class MapManager
{

public:
	void InitializeMap1(); // 초기맵생성
	void InitializeMap2(); // 초기맵생성

	void PrintMap(Player* player,Enemy* enemy); // 현재맵상태 프린트
	void TileStateChange(int posX, int posY, int TileState);
	bool CanMove(int posX, int posY) const; //플레이어 이동가능한곳인지
	bool CanBreak(int inPosX, int inPosY) const; //폭탄이 부술수있는곳인지
	bool isPlayerHit(int inPosX, int inPosY, Player* player) const; //플레이어 맞았는지
	bool isEnemyHit(int inPosX, int inPosY) const; //적 맞았는지
	bool isBreakableHit(int inPosX, int inPosY) const; //부술수 있는 벽 맞았는지
	int RemainEnemy = 1;
	static const int MapSize = 11;
	int Map[MapSize][MapSize];
};

#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"

enum class MTileState
{

	Road = 0,
	Wall = 1,
	SoftRock = 10,
	Bomb = 20,
	HitBombEffect = 21,
	Player = 50,
	Enemy = 60
};
class MapManager
{

public:
	//스테이지 1, 2 초기값 세팅
	void InitializeMap1(Player* player,Enemy* enemy, Enemy* enemy2); // 초기맵생성
	void InitializeMap2(Player* player,Enemy* enemy,Enemy* enemy2); // 초기맵생성
	// 현재맵상태 프린트
	void PrintMap(Player* player, Enemy* enemy1, Enemy* enemy2);
	//플레이어,적 이동가능한곳인지
	bool CanMove(int posX, int posY) const; 
	//폭탄이 부술수있는곳인지
	bool CanBreak(int inPosX, int inPosY) const; 
	//플레이어 맞았는지
	bool isPlayerHit(int inPosX, int inPosY, Player* player) const;
	//적 맞았는지
	bool isEnemyHit(int inPosX, int inPosY, Enemy* enemy) const;
	//부술수 있는 벽 맞았는지

	bool isBreakableHit(int inPosX, int inPosY) const; 
	const int Stage1RemainEnemy = 2;
	const int Stage2RemainEnemy = 2;
	int RemainEnemy;
	static const int MapSize = 11;
	int Map[MapSize][MapSize];
};

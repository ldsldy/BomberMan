#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"

enum class MTileState
{
	Road = 0,         // 길
	Wall = 1,         // 부술 수 없는 벽
	SoftRock = 10,    // 부술 수 있는 벽
	Bomb = 20,        // 폭탄
	HitBombEffect = 21, // 폭발 효과
	Player = 50,      // 플레이어
	Enemy = 60        // 적
};
class MapManager
{

public:
	//스테이지 1, 2 초기값 세팅
	void InitializeMap1(Player* player,Enemy* enemy, Enemy* enemy2); // 초기맵생성
	void InitializeMap2(Player* player,Enemy* enemy,Enemy* enemy2); // 초기맵생성
	// 현재맵상태 프린트
	void PrintMap(Player* player, Enemy* enemy1, Enemy* enemy2);
	// --- 충돌 및 상태 확인 함수 ---
	bool CanMove(int posX, int posY) const; // 해당 좌표로 이동 가능한지 확인
	bool CanBreak(int inPosX, int inPosY) const; // 해당 좌표가 폭탄으로 파괴 가능한지 확인
	bool isPlayerHit(int inPosX, int inPosY, Player* player) const; // 플레이어가 맞았는지 확인
	bool isEnemyHit(int inPosX, int inPosY, Enemy* enemy) const;   // 적이 맞았는지 확인
	bool isBreakableHit(int inPosX, int inPosY) const; // 부술 수 있는 벽이 맞았는지 확인
	// --- 맵 데이터 ---
	const int Stage1RemainEnemy = 2; // 스테이지 1의 적 수
	const int Stage2RemainEnemy = 2; // 스테이지 2의 적 수
	int RemainEnemy; // 현재 스테이지에 남은 적의 수
	static const int MapSize = 11; // 맵의 크기 (11x11)
	int Map[MapSize][MapSize]; // 맵 타일 데이터를 저장하는 2차원 배열
};

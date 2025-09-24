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

	GameManager() = default;
	~GameManager();
	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Bomb* bomb = new Bomb();
	void InitializeMap(); // 초기맵생성
	void PrintMap(); // 현재맵상태 프린트
	void Clear(); //동적할당 해제
	void StagePlay(); //본게임
	void ExplosiveTileChange(int inPosX,int inPosY); //폭발범위만큼 타일 바꿔줌
	void ExplosiveTileRemove(int inPosX,int inPosY); //폭발범위만큼 바꿔진 타일 원상태로
	bool CanMove(int posX, int posY); //플레이어 이동가능한곳인지
	bool UnBreakable(int inPosX, int inPosY); //폭탄이 부술수있는곳인지
	bool isClear(); //게임 클리어
	bool isHit(); //플레이어 or 적 맞았는지

	bool isPresentBomb = false;
	bool isStageClear = false;
	bool OnBomb = false;
	static const int MapSize = 11;
	int Map[MapSize][MapSize];
};


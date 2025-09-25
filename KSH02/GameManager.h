#pragma once
#include "MapManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"

class GameManager
{
public:

	GameManager() = default;
	~GameManager();
	MapManager mapManager;
	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Bomb* bomb = new Bomb();
	void Clear(); //동적할당 해제
	void StagePlay(); //본게임
	void PlayerMoveXPlus();
	void PlayerMoveXMinus();
	void PlayerMoveYMinus();
	void PlayerMoveYPlus();
	void BombStateCheck(); //폭탄 시간감소및폭발 
	void PlaceBomb(); //폭탄 배치 함수
	void StageMenu();
	void ExplosiveTileChange(int inPosX,int inPosY); //폭발범위만큼 타일 바꿔줌
	void ExplosiveTileRemove(int inPosX,int inPosY); //폭발범위만큼 바꿔진 타일 원상태로
	bool isClear(); //게임 클리어
	void isHit(int inPosX, int inPosY);
	bool isPresentBomb = false; //폭발트리거 폭탄존재확인 bool
	bool WasPresentBomb = false; //폭발타일제거트리거  bool
	bool isStageClear = false;
	bool OnBomb = false;
	static const int MapSize = 11;
	int Map[MapSize][MapSize];
};


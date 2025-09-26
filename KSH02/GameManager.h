#pragma once
#include "MapManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"
#include <vector>
#include <utility>
class GameManager
{
public:

	GameManager() = default;
	~GameManager()=default;
	MapManager mapManager;
	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Enemy* enemy2 = new Enemy();
	std::vector<Bomb*> bombs; // 폭탄 여러개
	void Clear(); //동적할당 해제
	void StagePlay(int StageNum); //본게임
	void EnemyYMove(Enemy* enemy); 
	void KeyChange(char& PlayerSelect); //입력받는 char int로 변환
	

	//플레이어 이동함수 4방향
	void PlayerMoveXPlus();
	void PlayerMoveXMinus();
	void PlayerMoveYMinus();
	void PlayerMoveYPlus();
	//폭탄 배치 및 폭탄 별 시간감소 
	void BombStateCheck(); 
	void PlaceBomb();
	void ExplosiveTileChange(Bomb* bomb); //폭발범위만큼 타일 바꿔줌
	void ExplosiveTileRemove(Bomb* bomb); //폭발범위만큼 바꿔진 타일 원상태로
	
	void StageMenu();
	//트리거용 bool변수
	bool isHit(int inPosX, int inPosY);
	bool isStageClear = false;
	bool isStage1Clear = false;
	bool isStage2Clear = false;
	bool isStageFail = false;


};


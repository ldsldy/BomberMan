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
	// --- 게임 객체들 ---
	MapManager mapManager;
	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Enemy* enemy2 = new Enemy();
	std::vector<Enemy*> Enemys;
	std::vector<Bomb*> bombs; // 여러 개의 폭탄을 관리하는 벡터

	// --- 게임 흐름 제어 함수 ---
	void Clear(); // 게임 종료 시 동적 할당된 메모리 해제
	void StagePlay(int StageNum); // 실제 게임 플레이가 진행되는 함수
	void StageMenu(); // 스테이지 선택 및 업그레이드 메뉴

	// --- 객체별 행동 함수 ---
	void EnemyYMove(Enemy* enemy);
	void EnemyXMove(Enemy* enemy);
	void KeyChange(char& PlayerSelect); // 사용자 입력(char)을 내부 로직(int)으로 변환
	void PlayerMoveXPlus();
	void PlayerMoveXMinus();
	void PlayerMoveYMinus();
	void PlayerMoveYPlus();
	// --- 폭탄 관련 로직 함수 ---
	void BombStateCheck(); // 모든 폭탄의 상태(시간 감소, 폭발 등)를 업데이트
	void PlaceBomb();      // 플레이어 위치에 폭탄 설치
	void ExplosiveTileChange(Bomb* bomb); // 폭발 범위의 타일을 폭발 효과로 변경
	void ExplosiveTileRemove(Bomb* bomb); // 폭발 효과 타일을 다시 길로 변경
	
	// --- 상태 확인 및 트리거 ---
	bool isHit(int inPosX, int inPosY); // 특정 좌표에 폭탄이 닿았을 때 충돌 처리
	bool isStageClear = false;  // 스테이지 클리어 여부
	bool isStageFail = false;   // 스테이지 실패 여부
};


#pragma once
#include "Actor.h"
class Player :public Actor
{
public:

	Player() = default;
	virtual ~Player();

	// --- Getter 함수들 ---
	inline int ExpectedGetPosY() const { return ExpectedPosY; } // 이동 예정 y좌표
	inline int ExpectedGetPosX() const { return ExpectedPosX; } // 이동 예정 x좌표
	inline int GetPosX() override { return PosX; }
	inline int GetPosY() override { return PosY; }
	inline int GetHP() override { return HP; }

	// --- Actor로부터 상속받아 구현한 함수들 ---
	void setDefault(int x, int y) override;
	int TakeDamage(int indamage) override;

	// --- Player 이동 관련 함수 ---
	void PosXMove() override; // x축으로 최종 이동 확정
	void PosYMove() override; // y축으로 최종 이동 확정
	void ExpectedPosXMove(int inPosX); // x축 이동 예상 위치 계산
	void ExpectedPosYMove(int inPosY); // y축 이동 예상 위치 계산

	// --- Player 상태 및 능력치 ---
	bool isDead = false;
	int UpgradeChance = 1;    // 업그레이드 가능 횟수
	int maxBombs = 1;         // 설치 가능한 최대 폭탄 개수
	int currentBombs = 0;     // 현재 설치된 폭탄 개수
	int bombRange = 2;        // 폭탄의 폭발 범위
private:
	int ExpectedPosX = 1;
	int ExpectedPosY = 1;
	int PosX = 1;
	int PosY = 1;
	int HP = 5;
	const int defaultHp = 5; // 기본 체력
};


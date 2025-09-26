#pragma once
#include "Actor.h"

class Enemy : public Actor
{

public:
	Enemy() = default;

	// --- Actor로부터 상속받아 구현한 함수들 ---
	inline int GetPosX() override { return PosX; }
	inline int GetPosY() override { return PosY; }
	inline int GetHP() override { return HP; }

	void setDefault(int x, int y) override; // 적의 초기 위치와 상태 설정
	int TakeDamage(int indamage) override; // 데미지를 받는 처리

	// --- Enemy 고유 함수 ---
	void PosXMove(int inPosX); // x축으로 이동
	void PosYMove(int inPosY); // y축으로 이동

	// --- Enemy 상태 변수 ---
	bool MoveDir = false; // 이동 방향 (상하/좌우) 제어
	bool isDead = false;  // 사망 여부

private:
	int PosX = 9;
	int PosY = 9;
	int HP = 1;
	const int defaultHp = 1; // 기본 체력
};


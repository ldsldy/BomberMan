#pragma once
#include "Actor.h"
class Player :public Actor
{
public:

	Player() = default;
	virtual ~Player();

	//getter 함수들 
	inline int ExpectedGetPosY() const { return ExpectedPosY; }
	inline int ExpectedGetPosX() const { return ExpectedPosX; }
	inline int GetPosX() override { return PosX; }
	inline int GetPosY() override { return PosY; }
	inline int GetHP() override { return HP; }

	//기본 위치 초기값 세팅
	void setDefault(int x,int y) override; 
	//폭탄 데미지 받으면
	int TakeDamage(int indamage) override;
	//플레이어 이동함수
	void PosXMove() override; 
	void PosYMove() override; 
	void ExpectedPosXMove(int inPosX);
	void ExpectedPosYMove(int inPosY);
	
	bool isDead = false;
	int UpgradeChance = 1;
	int maxBombs = 1; // 최대 폭탄 개수
	int currentBombs = 0; // 현재 설치된 폭탄 개수
	int bombRange = 2; 

private:
	int ExpectedPosX =1;
	int ExpectedPosY =1;
	int PosX = 1;
	int PosY= 1;
	int HP = 5;
	const int defaultHp = 5;
};


#pragma once
#include "Actor.h"
class Player :public Actor
{
public:

	Player() = default;
	virtual ~Player();


	inline int ExpectedGetPosY() const { return ExpectedPosY; }
	inline int ExpectedGetPosX() const { return ExpectedPosX; }
	inline int GetPosX() override { return PosX; }
	inline int GetPosY() override { return PosY; }
	inline int GetHP() override { return HP; }
	void setDefault(int x,int y) override; 
	int TakeDamage(int indamage) override;
	void PosXMove() override; 
	void PosYMove() override; 
	void ExpectedPosXMove(int inPosX);
	void ExpectedPosYMove(int inPosY);
	
	bool isDead = false;
	int UpgradeChance = 0;
private:
	int ExpectedPosX =1;
	int ExpectedPosY =1;
	int PosX = 1;
	int PosY= 1;
	int HP = 5;
	const int defaultHp = 5;
};


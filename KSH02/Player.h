#pragma once
#include "Actor.h"
class Player
{
public:

	Player() = default;
	~Player();


	inline int ExpectedGetPosY() { return ExpectedPosY; }
	inline int ExpectedGetPosX() { return ExpectedPosX; }
	inline int GetPosX() { return PosX; }
	inline int GetPosY() { return PosY; }
	inline int GetHP() { return HP; }
	
	int TakeDamage(int indamage);
	void PosXMove();
	void PosYMove();
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
	const int StartPosX = 1;
	const int StartPosY = 1;
};


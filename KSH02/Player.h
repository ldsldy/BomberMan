#pragma once
#include "Actor.h"
class Player
{
public:

	Player() = default;
	~Player();


	inline int GetPosX() { return PosX; }
	inline int GetPosY() { return PosY; }
	inline int GetHP() { return HP; }
	
	int TakeDamage(int indamage);
	void PosXMove(int inPosX);
	void PosYMove(int inPosY);

private:
	int PosX = 1;
	int PosY= 1;
	int HP = 5;
	const int StartPosX = 1;
	const int StartPosY = 1;
};


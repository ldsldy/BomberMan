#include "Player.h"

Player::~Player()
{
	
}

int Player::TakeDamage(int indamage)
{
	HP -= indamage;
	return HP;
}

void Player::PosXMove(int inPosX)
{
	PosX += inPosX;
}

void Player::PosYMove(int inPosY)
{
	PosY += inPosY;
}



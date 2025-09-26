#include "Player.h"

Player::~Player()
{
}

void Player::setDefault(int x, int y)
{
	PosX = x;
	PosY = y;
	HP = defaultHp;
}

int Player::TakeDamage(int indamage)
{
	HP -= indamage;
	if (HP <= 0) {
		isDead = true;
	}

	return HP;
}

void Player::PosXMove()
{
	PosX = ExpectedPosX;
}

void Player::PosYMove()
{
	PosY  = ExpectedPosY;
}

void Player::ExpectedPosXMove(int inPosX)
{
	ExpectedPosX = inPosX+ PosX;
}

void Player::ExpectedPosYMove(int inPosY)
{
	ExpectedPosY = inPosY+ PosY;
}



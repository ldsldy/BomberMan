#pragma once
class Bomb
{
public:
	Bomb() = default;
	bool isExplosive();
	


	int PosX = -1;
	int PosY = -1;
	int ExplosiveTime = 5;
	int ExplosiveRemoveTime = 2;
	const int DefaultExplosiveTime = 5;
	int ExplosiveRange = 2;
};


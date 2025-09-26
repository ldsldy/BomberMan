#pragma once
class Bomb
{
public:
	Bomb() = default;
	bool isExplosive();
	
	enum class BombState
	{
		Ticking,
		Exploding
	};

	int PosX = -1;
	int PosY = -1;
	int ExplosiveTime = 5;
	const int DefaultExplosiveTime = 5;
	int ExplosiveRemoveTime = 3;
	const int DefaultExplosiveRemoveTime = 3;
	int ExplosiveRange = 2;
	BombState state = BombState::Ticking;
};


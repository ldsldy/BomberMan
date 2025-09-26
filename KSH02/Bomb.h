#pragma once
#include <vector>   
#include <utility>  
class Bomb
{
public:
	Bomb() = default;
	Bomb(int range);
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
	//ÆøÅº»óÅÂ
	BombState state = BombState::Ticking;
	//ÅÍ¶ß·È´ø Å¸ÀÏÀ§Ä¡ ÀúÀå
	std::vector<std::pair<int, int>> changedTiles;
};


#pragma once
class Player
{
public:

	Player() = default;
	~Player();
	inline int GetPlayerStartPosX() { return PlayerStartPosX; }
	inline int GetPlayerStartPosY() { return PlayerStartPosY; }

	void PlaceBomb();

private:
	int PlayerPosX = 1;
	int PlayerPosY= 1;
	const int PlayerStartPosX = 1;
	const int PlayerStartPosY = 1;
};


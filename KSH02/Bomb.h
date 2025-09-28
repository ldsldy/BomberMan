#pragma once
#include <vector>   
#include <utility>  
#include <map>
#include <set>
class Bomb
{
public:
	Bomb() = default;
	Bomb(int range); // 플레이어의 업그레이드된 범위를 받아 생성
	bool isExplosive(); // 폭발할 시간인지 확인
	// 폭탄의 상태
	enum class BombState
	{
		Ticking,
		Exploding
	};
	// --- 폭탄 속성 ---
	int PosX = -1; // 설치된 x좌표
	int PosY = -1; // 설치된 y좌표
	int ExplosiveTime = 5; // 폭발까지 남은 턴
	const int DefaultExplosiveTime = 5; // 폭발 시간 초기값
	int ExplosiveRemoveTime = 3; // 폭발 효과가 사라지기까지 남은 턴
	const int DefaultExplosiveRemoveTime = 3; // 폭발 효과 시간 초기값
	int ExplosiveRange = 2; // 폭발 범위

	BombState state = BombState::Ticking; // 현재 폭탄 상태
	std::vector<std::pair<int, int>> changedTiles; // 폭발로 인해 변경된 타일 좌표 저장;
};
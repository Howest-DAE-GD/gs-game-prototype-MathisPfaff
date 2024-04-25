#include "Vector2f.h"

#pragma once
class Player
{
public:
	enum LR
	{
		Left,
		Right
	};

	Player();
	~Player();

	void Draw();
	void Update(float elapsedSec);
	void KeyDownEvent(const SDL_KeyboardEvent& e);
	void KeyUpEvent(const SDL_KeyboardEvent& e);

private:
	Point2f m_PositionFirst;
	Point2f m_PositionSecond;
	LR m_IsLooking;
	Vector2f m_Speed;
	bool m_Jump;

};


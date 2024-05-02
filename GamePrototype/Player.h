#include "Vector2f.h"

#pragma once
class Player
{
public:
	enum LR
	{
		Left,
		Right,
	};

	Player();
	~Player();

	void Draw();
	void Update(float elapsedSec);
	void KeyDownEvent(const SDL_KeyboardEvent& e);
	void KeyUpEvent(const SDL_KeyboardEvent& e);

	Point2f GetPos();

private:
	Point2f m_PositionFirst;
	Point2f m_PositionSecond;
	LR m_IsLooking;
	bool Isleft;
	bool IsRight;
	Vector2f m_Speed;
	bool m_Jump;
	int TakePoint;
	static const int PREVIOUS_POINTS{10};
	Point2f LastPositions[PREVIOUS_POINTS];

};


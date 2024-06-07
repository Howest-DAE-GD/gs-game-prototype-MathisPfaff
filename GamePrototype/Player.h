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
	void HitX(float given_X);
	void HitY(float given_Y);
	void InGhost();

	Point2f GetPos();
	Rectf GetHitbox();
	bool Getdirection();
	Vector2f GetSpeed();

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
	Rectf m_Hitbox;
	bool Falling;
	bool GhostActive;
	float Cooldown;
	bool doubleJump;
};


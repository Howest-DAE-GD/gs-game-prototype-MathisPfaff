#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>

Player::Player() :
	m_Speed{ 400.f, 0.f }, m_PositionFirst{ 200.f, 200.f }, m_PositionSecond{ 180.f, 200.f }, m_IsLooking{ LR::Right },
	m_Jump{ true }, TakePoint{ 0 }, Isleft{ false }, IsRight{ false }, m_Hitbox{ 200.f, 200.f, 80.f, 80.f }, Falling{ false }, GhostActive{ false },
	Cooldown{ 2.f }, doubleJump{ false }
{}
Player::~Player()
{}


void Player::Draw()
{
	//utils::DrawRect(m_Hitbox);
	utils::SetColor(Color4f{ 0.f, 0.776f, 1.f, 1.f });
	utils::FillEllipse(m_PositionSecond.x, m_PositionSecond.y, 40.f, 40.f);
	utils::SetColor(Color4f{ 0.133f, 0.776f, 0.267f, 1.f });
	utils::FillEllipse(m_PositionFirst.x, m_PositionFirst.y, 40.f, 40.f);
}
void Player::Update(float elapsedSec)
{
	m_PositionFirst.x = m_Hitbox.left + 40.f;
	m_PositionFirst.y = m_Hitbox.bottom + 40.f;

	//std::cout << m_Hitbox.left << "." << m_Hitbox.bottom << std::endl;
	for (int index{ PREVIOUS_POINTS - 1 }; index > 0; --index)
	{
		LastPositions[index] = LastPositions[index - 1];
	}

	LastPositions[0] = m_PositionFirst;
		
	
	if (Isleft)
	{
		m_Speed.x = -400.f;
		m_Hitbox.left += m_Speed.x * elapsedSec;
	}
	if (IsRight)
	{
		m_Speed.x = 400.f;
		m_Hitbox.left += m_Speed.x * elapsedSec;
	}
	
	if (GhostActive == false)
	{
		if (m_IsLooking == LR::Right)
		{
			float Xlength{ m_PositionFirst.x - 50 - m_PositionSecond.x };
			m_PositionSecond.x += Xlength * elapsedSec * 5;
		}
		else if (m_IsLooking == LR::Left)
		{
			float Xlength{ m_PositionFirst.x + 50 - m_PositionSecond.x };
			m_PositionSecond.x += Xlength * elapsedSec * 5;
		}

		Cooldown = 2.f;
	}

	if (Falling)
	{
		InGhost();

		m_Hitbox.bottom += m_Speed.y;

		if (GhostActive == false)
		{
			m_PositionSecond.y = LastPositions[PREVIOUS_POINTS - 1].y;
		}
		
		m_Speed.y -= 9.f * elapsedSec;
	}
	else
	{
		if (GhostActive == false)
		{
			m_PositionSecond.y = LastPositions[PREVIOUS_POINTS - 1].y;
		}
		m_Speed.y = 0.f;
		m_Jump = true;
	}
	
	if (GhostActive) Cooldown -= elapsedSec;

}


void Player::KeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
	case SDLK_SPACE:
		if (m_Jump)
		{
			m_Speed.y = 5.f;
			m_Jump = false;
			Falling = true;
		}
		if (doubleJump == true)
		{
			m_Speed.y = 5.f;
			Falling = true;
		}
		break;
	case SDLK_a:
		Isleft = true;
		m_IsLooking = LR::Left;
		break;
	case SDLK_d:
		IsRight = true;
		m_IsLooking = LR::Right;
		break;
	case SDLK_q:
		
		if (GhostActive == false)
		{
			m_PositionSecond = m_PositionFirst;
			GhostActive = true;
		}
		
		break;
	case SDLK_e:

		if (GhostActive)
		{
			if (Cooldown < 0)
			{
				GhostActive = false;
				doubleJump = false;
			}
		}
	}
}
void Player::KeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_a:
		Isleft = false;
		break;
	case SDLK_d:
		IsRight = false;
		break;
	}
}


Point2f Player::GetPos()
{
	return m_PositionFirst;
}

Rectf Player::GetHitbox()
{
	return m_Hitbox;
}

bool Player::Getdirection()
{
	return Isleft;
}

Vector2f Player::GetSpeed()
{
	return m_Speed;
}

void Player::HitX(float given_X)
{
	if (given_X != 0)
	{
		m_Hitbox.left = given_X;
	}
}
void Player::HitY(float given_Y)
{
	if (given_Y != 0)
	{
		if (given_Y < 0)
		{
			m_Hitbox.bottom = -given_Y;
			m_Speed.y = 0.f;
		}
		else
		{
			m_Hitbox.bottom = given_Y;
			Falling = false;
		}

		
	}
	else
	{
		Falling = true;
	}
}

void Player::InGhost()
{
	if (GhostActive)
	{
		const Rectf Ghost{ m_PositionSecond.x - 40.f, m_PositionSecond.y - 40.f, 80.f, 80.f };

		if (utils::IsOverlapping(m_Hitbox, Ghost))
		{
			doubleJump = true;
		}
		else
		{
			doubleJump = false;
		}
	}
}
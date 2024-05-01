#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>

Player::Player() :
	m_Speed{ 0.f, 0.f }, m_PositionFirst{ 200.f, 200.f }, m_PositionSecond{ 180.f, 200.f }, m_IsLooking{},
	m_Jump{ true }, TakePoint{0}
{}
Player::~Player()
{}


void Player::Draw()
{
	utils::SetColor(Color4f{ 0.f, 0.776f, 1.f, 1.f });
	utils::FillEllipse(m_PositionSecond.x, m_PositionSecond.y, 40.f, 50.f);
	utils::SetColor(Color4f{ 0.133f, 0.776f, 0.267f, 1.f });
	utils::FillEllipse(m_PositionFirst.x, m_PositionFirst.y, 40.f, 50.f);
}
void Player::Update(float elapsedSec)
{
	if (TakePoint == 0)
	{
		for (int index{ PREVIOUS_POINTS - 1 }; index > 0; --index)
		{
			LastPositions[index] = LastPositions[index - 1];
		}

		LastPositions[0] = m_PositionFirst;
		TakePoint = 2;
	}
	else
	{
		--TakePoint;
	}
	
	
	m_PositionFirst.x += m_Speed.x * elapsedSec;
	

	if (m_IsLooking == LR::Right)
	{
		float Xlength{ m_PositionFirst.x - 50 - m_PositionSecond.x };
		m_PositionSecond.x += Xlength  * elapsedSec * 2;
	}
	else if(m_IsLooking == LR::Left)
	{
		float Xlength{ m_PositionFirst.x + 50 - m_PositionSecond.x };
		m_PositionSecond.x += Xlength * elapsedSec;
	}

	if (m_PositionFirst.y >= 200.f)
	{
		m_PositionFirst.y += m_Speed.y;

		m_PositionSecond.y = LastPositions[2].y;
		
		m_Speed.y -= 9.f * elapsedSec;
	}
	else
	{
		m_PositionFirst.y = 200.f;
		m_Speed.y = 0.f;
		m_Jump = true;
	}

	//if (m_PositionSecond.y < 200.f)
	//{
		//m_PositionSecond.y = 200.f;
	//}
	
}


void Player::KeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
	case SDLK_a:
		m_Speed.x = -200.f;
		m_IsLooking = LR::Left;
		break;
	case SDLK_d:
		m_Speed.x = 200.f;
		m_IsLooking = LR::Right;
		break;
	case SDLK_SPACE:
		if (m_Jump == true)
		{
			m_Speed.y = 5.f;
			m_Jump = false;
		}
		break;
	}
}
void Player::KeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_a:
		m_Speed.x = 0.f;
		break;
	case SDLK_d:
		m_Speed.x = 0.f;
		break;
	}
}
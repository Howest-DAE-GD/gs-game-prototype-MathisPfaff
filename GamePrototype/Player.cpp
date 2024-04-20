#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>

Player::Player() :
	m_Speed{0.f, 4.f}, m_PositionFirst{200.f, 200.f}, m_PositionSecond{180.f, 200.f}
{}
Player::~Player()
{}


void Player::Draw()
{
	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	utils::FillEllipse(m_PositionSecond.x, m_PositionSecond.y, 40.f, 50.f);
	utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 1.f });
	utils::FillEllipse(m_PositionFirst.x, m_PositionFirst.y, 40.f, 50.f);
}
void Player::Update(float elapsedSec)
{
	m_PositionFirst.x += m_Speed.x * elapsedSec;
	

	if (m_IsLooking == LR::Right)
	{
		float Xlength{ m_PositionFirst.x - 50 - m_PositionSecond.x };
		m_PositionSecond.x += Xlength  * elapsedSec;
	}
	else if(m_IsLooking == LR::Left)
	{
		float Xlength{ m_PositionFirst.x + 50 - m_PositionSecond.x };
		m_PositionSecond.x += Xlength * elapsedSec;
	}
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
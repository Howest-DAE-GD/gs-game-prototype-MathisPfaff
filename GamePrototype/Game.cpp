#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "utils.h"
#include "SVGParser.h"
#include <vector>
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Player = new Player{};
	SVGParser::GetVerticesFromSvgFile("LevelTowerV8.svg", m_SolidHitboxes);
}

void Game::Cleanup( )
{
	delete m_Player;
}

void Game::Update( float elapsedSec )
{
	m_Player->Update(elapsedSec);
	m_Player->HitY(CheckHitFalling(m_Player->GetHitbox(), m_Player->GetSpeed().y));
	m_Player->HitX(CheckHitWall(m_Player->GetHitbox(), m_Player->GetSpeed().x));
	m_cameraPos = Point2f{ m_Player->GetPos().x - GetViewPort().width / 2, m_Player->GetPos().y - 200.f};
}

void Game::Draw( ) const
{
	ClearBackground();

	glPushMatrix();
	{
		glTranslatef(-m_cameraPos.x, -m_cameraPos.y, 0);

		utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
		utils::FillRect(Point2f{ 100.f, 150.f }, 200.f, 200.f);

		m_Player->Draw();

		for (std::vector<Point2f> vector : m_SolidHitboxes)
		{
			utils::DrawPolygon(vector);
		}
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player->KeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_Player->KeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


float Game::CheckHitFalling(const Rectf& given_hitbox, float speed)
{
	Point2f LB{ given_hitbox.left, given_hitbox.bottom };
	Point2f LT{ given_hitbox.left, given_hitbox.bottom + given_hitbox.height };
	Point2f RB{ given_hitbox.left + given_hitbox.width, given_hitbox.bottom };
	Point2f RT{ given_hitbox.left + given_hitbox.width, given_hitbox.bottom + given_hitbox.height };

	Point2f intersectionPoint1{};
	Point2f intersectionPoint2{};

	float result{ 0 };

	utils::HitInfo hitInfo;

	for (std::vector<Point2f> vector : m_SolidHitboxes)
	{
		if (speed > 0)
		{
			if (utils::Raycast(vector, LT, LB, hitInfo))
			{
				intersectionPoint1 = hitInfo.intersectPoint;

				float dif{ hitInfo.lambda * (LT.y - LB.y) };

				result = given_hitbox.bottom - dif - 1.f;
				result = -result;
			}
			if (utils::Raycast(vector, RT, RB, hitInfo))
			{
				intersectionPoint2 = hitInfo.intersectPoint;

				if (intersectionPoint2.y > intersectionPoint1.y)
				{
					float dif{ hitInfo.lambda * (RT.y - RB.y) };

					result = given_hitbox.bottom - dif - 1.f;
					result = -result;
				}
			}
		}
		else
		{
			if (utils::Raycast(vector, LB, LT, hitInfo))
			{
				intersectionPoint1 = hitInfo.intersectPoint;

				float dif{ hitInfo.lambda * (LT.y - LB.y) };

				result = given_hitbox.bottom + dif;
			}
			if (utils::Raycast(vector, RB, RT, hitInfo))
			{
				intersectionPoint2 = hitInfo.intersectPoint;

				if (intersectionPoint2.y > intersectionPoint1.y)
				{
					float dif{ hitInfo.lambda * (RT.y - RB.y) };

					result = given_hitbox.bottom + dif;
				}
			}
		}
	}




	return result;
}

float Game::CheckHitWall(const Rectf& given_hitbox, float speed)
{
	Point2f LB{ given_hitbox.left, given_hitbox.bottom };
	Point2f LT{ given_hitbox.left, given_hitbox.bottom + given_hitbox.height };
	Point2f RB{ given_hitbox.left + given_hitbox.width, given_hitbox.bottom };
	Point2f RT{ given_hitbox.left + given_hitbox.width, given_hitbox.bottom + given_hitbox.height };

	Point2f intersectionPoint1{};
	Point2f intersectionPoint2{};

	float result{ 0 };

	utils::HitInfo hitInfo;

	for (std::vector<Point2f> vector : m_SolidHitboxes)
	{
		if (speed < 0)
		{
			if (utils::Raycast(vector, LT, RT, hitInfo))
			{
				intersectionPoint1 = hitInfo.intersectPoint;

				float inShape{ hitInfo.lambda * (RT.x - LT.x) };

				result = given_hitbox.left + inShape + 1.f;
			}
			if (utils::Raycast(vector, LB, RB, hitInfo))
			{
				intersectionPoint2 = hitInfo.intersectPoint;

				if (intersectionPoint2.x < intersectionPoint1.x)
				{
					float inShape{ hitInfo.lambda * (RB.x - LB.x) };

					result = given_hitbox.left + inShape + 1.f;
				}
			}
		}
		else
		{
			if (utils::Raycast(vector, RT, LT, hitInfo))
			{
				intersectionPoint1 = hitInfo.intersectPoint;

				float inShape{ hitInfo.lambda * (RT.x - LT.x)};

				result = given_hitbox.left - inShape- 1.f;

			}
			if (utils::Raycast(vector, RB, LB, hitInfo))
			{
				intersectionPoint2 = hitInfo.intersectPoint;

				if (intersectionPoint2.x < intersectionPoint1.x)
				{
					float inShape{ hitInfo.lambda * (RB.x - LB.x)};

					result = given_hitbox.left - inShape - 1.f;
				}
			}
		}
	}

	return result;
}
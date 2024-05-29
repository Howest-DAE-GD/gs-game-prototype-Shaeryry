#include "pch.h"
#include "Game.h"
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
	// Player init
	m_Player = new Player(); 

	// Boss init
	m_Boss = new Boss(m_Player);
	m_Boss->SetColor(Color4f(1, 0, 0, 1));
	m_Boss->SetPosition(Vector2f(-BOSS_OFFSET, (GetViewPort().height / 2) ));

	AddHumanoid(m_Player);
	AddHumanoid(m_Boss);

}

void Game::Cleanup( )
{
	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		delete m_Humanoids[humanoidIndex];
	};
}

void Game::Update( float elapsedSec )
{
	// Movement logic
	m_Boss->MoveTo(elapsedSec, m_Boss->GetPosition() + Vector2f(1, 0));
	m_Player->MoveTo(elapsedSec, m_Player->GetPosition() + Vector2f(1, 0));

	// Humanoid updates
	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		m_Humanoids[humanoidIndex]->Update(elapsedSec);
	};
}

void Game::Draw( ) const
{
	ClearBackground( );
	const float CAMERA_X{ -m_Player->GetPosition().x + (GetViewPort().width / 2) };

	// Ground
	utils::SetColor(Color4f(1, 1, 1, 1));
	utils::DrawRect(Rectf(0, 0, GetViewPort().width*1.25f, GROUND_HEIGHT));

	glPushMatrix();
	glTranslatef(CAMERA_X, 0, 0);
	glRotatef(0, 0, 0, 1);

		for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
			m_Humanoids[humanoidIndex]->Draw();
		};

	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_Player->ProcessKeyUpEvent(e);
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
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

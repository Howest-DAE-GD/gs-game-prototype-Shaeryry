#include "pch.h"
#include "Game.h"
#include "Sword.h"
#include "Enemy.h"

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
	m_Ball = new Ball( Vector2f( GetViewPort().width/2,GetViewPort().height/2 ) );
	m_Player = new Player();
	AddHumanoid(m_Player);
	m_Ball->SetTarget(m_Player);

	Enemy* newEnemy{ new Enemy(m_Ball) };
	newEnemy->SetPosition(Vector2f(GetViewPort().width / 2, GetViewPort().height / 2));
	AddEnemy(newEnemy);
}

void Game::Cleanup( )
{
	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		delete m_Humanoids[humanoidIndex];
	};

	delete m_Ball;
}

void Game::Update( float elapsedSec )
{
	m_Ball->Update(elapsedSec);
	// Ball logic

	// Humanoid updates
	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		m_Humanoids[humanoidIndex]->Update(elapsedSec);
	};
}

void Game::Draw( ) const
{
	ClearBackground( );

	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		m_Humanoids[humanoidIndex]->Draw();
	};
	m_Ball->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player->ProcessKeyDownEvent(e);
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_Player->ProcessKeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	if (m_Player->GetWeapon() != nullptr) {
		m_Player->GetWeapon()->SetTarget(Vector2f(float(e.x), float(e.y)));
	}
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_Player->AttackPlayer(Point2f(float(e.x), float(e.y)), m_Ball, m_Humanoids);
		break;
	default:
		break;
	}
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

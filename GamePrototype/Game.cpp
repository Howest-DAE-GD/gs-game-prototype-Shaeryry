#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>

// Pick ups
#include "Point.h"

//

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
	m_State = GameState::Start;

	// Player init
	m_Player = new Player(); 

	// Boss init
	m_Boss = new Boss(m_Player);
	m_Boss->SetColor(Color4f(1, 0, 0, 1));

	AddHumanoid(m_Player);
	AddHumanoid(m_Boss);

	Reset();

}

void Game::Cleanup( )
{
	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		delete m_Humanoids[humanoidIndex];
	};

	for (size_t pickUpIndex{}; pickUpIndex < m_Touchables.size(); pickUpIndex++) {
		delete m_Touchables[pickUpIndex];
	};
}

void Game::Update( float elapsedSec )
{
	const bool isPlaying{ m_State == GameState::Playing };
	const bool isAlive{ m_Player->GetHealth() > 0 };
	if (not isAlive) {
		m_State = GameState::Died;
	}
	// Pickups
	if (m_PickupClock >= m_NextCooldown) {
		for (int pickupIndex{ 1 }; pickupIndex < (rand() % PICK_UP_COUNT) + 1; pickupIndex++) {
			const float baseHeight{ (GROUND_HEIGHT + PICK_UP_SPAWN_BASE_HEIGHT) };
			const int height{ int(baseHeight) + rand() % int((WINDOW_HEIGHT - PICK_SPAWN_MARGIN) - UI_HEIGHT - baseHeight - (PICK_UP_DEFAULT_SIZE / 2)) };

			const Vector2f spawnPosition{
				 m_Player->GetPosition().x + (WINDOW_WIDTH * pickupIndex),
				 float(height)
			};

			AddTouchable(new Point(m_Player, spawnPosition));
		}

		m_PickupClock = 0;
		m_NextCooldown = (rand() % (PICK_UP_MAX_COOLDOWN - PICK_UP_MIN_COOLDOWN) ) + PICK_UP_MIN_COOLDOWN;
	};

	// Pickup updates
	for (size_t pickUpIndex{}; pickUpIndex < m_Touchables.size(); pickUpIndex++) {
		m_Touchables[pickUpIndex]->Update(elapsedSec);
	};


	// Movement logic
	m_Boss->MoveTo(elapsedSec, m_Boss->GetPosition() + Vector2f(1, 0));
	if (isAlive) {
		m_Player->MoveTo(elapsedSec, m_Player->GetPosition() + Vector2f(1, 0));
	}

	// Humanoid updates
	for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
		m_Humanoids[humanoidIndex]->Update(elapsedSec);
	};

	if (isPlaying) {
		m_PickupClock += elapsedSec;
		m_LiveClock += elapsedSec;
	};
	m_GameClock += elapsedSec;

}

void Game::Draw( ) const
{
	ClearBackground( );
	const float CAMERA_X{ -m_Player->GetPosition().x + (GetViewPort().width / 2) };
	glPushMatrix();
	glTranslatef(0, UI_HEIGHT, 0);

	// Ground
	utils::SetColor(Color4f(1, 1, 1, 1));
	utils::DrawRect(Rectf(0, 0, GetViewPort().width*1.25f, GROUND_HEIGHT));

	glPushMatrix();
	glTranslatef(CAMERA_X,0, 0);
	glRotatef(0, 0, 0, 1);


		// Pickup 
		for (size_t pickUpIndex{}; pickUpIndex < m_Touchables.size(); pickUpIndex++) {
			m_Touchables[pickUpIndex]->Draw();
		};

		for (size_t humanoidIndex{}; humanoidIndex < m_Humanoids.size(); humanoidIndex++) {
			m_Humanoids[humanoidIndex]->Draw();
		};

	glPopMatrix();
	glPopMatrix(); 

	utils::SetColor(Color4f(0, 0, 0, 1));
	utils::FillRect(Rectf(0,0,WINDOW_WIDTH,UI_HEIGHT));

	const float textSize{ 16.f * 1.25f };
	const float xCenter{ (WINDOW_WIDTH/2) };
	const float yCenter{ (UI_HEIGHT / 2) - textSize/2 };

	const float minutes{ std::floor(m_LiveClock /60 ) };
	const int seconds{ int(m_LiveClock) % 59 };
	const std::string clockDisplay{ std::to_string(int(minutes)) + ":" + std::to_string(seconds) };
		
	Texture scoreTexture{ "Score : " + std::to_string(m_Player->GetScore()) , "Minecraft.ttf",int(textSize),Color4f(1,1,1,1)};
	scoreTexture.Draw( Rectf( xCenter + 250.f ,yCenter,0,0) );

	Texture timeTexture{ "Time : " + std::to_string(int(std::floor(m_LiveClock))) + " s" , "Minecraft.ttf",int(textSize),Color4f(1,1,1,1)};
	timeTexture.Draw(Rectf(xCenter + 60.f, yCenter, 0, 0));

	for (int i{ 0 }; i < m_Player->GetHealth(); i++) {
		utils::SetColor(Color4f(1, 0, 0, 1));
		utils::FillRect(Rectf((xCenter - 315.f) + 25 * i, 10.f, 20, 50));
	};


	if (not (m_State == GameState::Playing)) {
		const int titleSize{ 36 };

		const float angle{ 8 };
		const float offset{ 50 };
		const float x{ xCenter };
		const float y{ (WINDOW_HEIGHT / 2) + offset };
		const float yMultiplier{ float(sin(2 * M_PI * (m_GameClock / 2.f))) };

		const std::string deathText{ "You have died with a score of " + std::to_string(m_Player->GetScore()) };
		const std::string titleText{ "Villain VS Jumpy boi !!!" };

		if (m_State == GameState::Died) {
			glPushMatrix();

			Texture endTextTexture{ deathText , "Minecraft.ttf" ,int(titleSize),Color4f(1,1,1,1) };

			glTranslatef(x, y, 0);
			glRotatef(angle * yMultiplier, 0, 0, 1);

			endTextTexture.Draw(Rectf(-endTextTexture.GetWidth() / 2, -offset/2 , 0, 0));
			glPopMatrix();

			// RESTART TEXT

			const float yInstruction{ ((WINDOW_HEIGHT / 2) - 25.f) - (5.f * yMultiplier) };
			Texture startInstructionTexture{ "press 'r' to restart" , "Minecraft.ttf" ,16,Color4f(1,1,0,1) };
			startInstructionTexture.Draw(Rectf(xCenter - (startInstructionTexture.GetWidth() / 2), yInstruction - (startInstructionTexture.GetHeight() / 2), 0, 0));
		}
		else if (m_State == GameState::Start) {
			// TITLE

			glPushMatrix();
			Texture titleTextTexture{ titleText , "Minecraft.ttf" ,int(titleSize),Color4f(1,1,1,1) };

			glTranslatef(x, y, 0);
			glRotatef(angle * yMultiplier, 0, 0, 1);

			titleTextTexture.Draw(Rectf(-titleTextTexture.GetWidth() / 2, -offset / 2, 0, 0));
			glPopMatrix();


			// CONTROLS

			const int fontSize{ 16 };
			const float xControls{ xCenter + 325.f };
			const float yControls{ ((WINDOW_HEIGHT / 2) + 200.f) + (5 * yMultiplier) };
			const float offsetPerControl{ 30 };
			int controlNumber{ 0 };


			Texture controlsTextTexture{ "== CONTROLS ==" , "Minecraft.ttf" ,fontSize,Color4f(1,1,1,1) };
			controlsTextTexture.Draw(Rectf(xControls - (controlsTextTexture.GetWidth() / 2), (yControls - (offsetPerControl * controlNumber)) - (controlsTextTexture.GetHeight() / 2), 0, 0));
			controlNumber++;

			Texture upTextTexture{ "JUMP - UP" , "Minecraft.ttf" ,fontSize,Color4f(1,1,1,1) };
			upTextTexture.Draw(Rectf(xControls - (upTextTexture.GetWidth() / 2), (yControls - (offsetPerControl * controlNumber)) - (upTextTexture.GetHeight() / 2), 0, 0));
			controlNumber++;
			
			Texture downTextTexture{ "FALL - DOWN" , "Minecraft.ttf" ,fontSize,Color4f(1,1,1,1) };
			downTextTexture.Draw(Rectf(xControls - (downTextTexture.GetWidth() / 2), (yControls - (offsetPerControl * controlNumber)) - (downTextTexture.GetHeight() / 2), 0, 0));

			// START TEXT

			const float yInstruction{ ((WINDOW_HEIGHT / 2) - 25.f) - (5.f * yMultiplier) };
			Texture startInstructionTexture{ "press 'r' to start !!" , "Minecraft.ttf" ,fontSize,Color4f(1,1,0,1) };
			startInstructionTexture.Draw(Rectf(xCenter - (startInstructionTexture.GetWidth() / 2), yInstruction - (startInstructionTexture.GetHeight() / 2), 0, 0));
		}
	}

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player->ProcessKeyDownEvent(e);
	switch (e.keysym.sym)
	{
	case SDLK_r:
		if (m_State != GameState::Playing) {
			Reset();
			m_State = GameState::Playing;
			m_Boss->SetActive(true);
		}
		break;
	default:
		break;
	}
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

void Game::Reset()
{
	m_GameClock = 0;
	m_PickupClock = 0;
	m_LiveClock = 0;
	m_NextCooldown = PICK_UP_MAX_COOLDOWN;

	m_Player->AddScore(-m_Player->GetScore());
	m_Player->SetPosition(Vector2f(0, 0));
	m_Player->SetHealth(PLAYER_HEALTH);

	m_Boss->SetPosition(Vector2f(-BOSS_OFFSET, (GetViewPort().height / 2)));
	m_Boss->Reset();
}

void Game::ClearBackground( ) const
{
	glClearColor( float(16.f/255.f), float(16.f/255.f), float(20.f/255.f), 1.f);
	glClear( GL_COLOR_BUFFER_BIT );
}

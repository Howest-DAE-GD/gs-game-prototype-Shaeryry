#pragma once
#include "BaseGame.h"
#include "Humanoid.h"
#include "Player.h"
#include "Ball.h"
#include "Enemy.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();
	 
	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	Player* m_Player;
	Ball* m_Ball;
	
	std::vector<Humanoid*> m_Humanoids;
	std::vector<Enemy*> m_Enemies;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void AddHumanoid(Humanoid* humanoid) { m_Humanoids.push_back(humanoid); };
	void AddEnemy(Enemy* enemy) { AddHumanoid(enemy); m_Enemies.push_back(enemy); };
};
#pragma once
#include "BaseGame.h"
#include "Humanoid.h"
#include "Boss.h"
#include "Player.h"
#include "Pickup.h"

enum class GameState {
	Start,
	Playing,
	Died,
};

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

	void Reset();
private:
	GameState m_State;
	float m_GameClock;
	float m_LiveClock;
	float m_PickupClock;
	int m_NextCooldown;
	Player* m_Player;
	Boss* m_Boss;
	
	std::vector<Humanoid*> m_Humanoids;
	std::vector<Pickup*> m_Touchables;
	//std::vector<Enemy*> m_Enemies;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void AddHumanoid(Humanoid* humanoid) { m_Humanoids.emplace_back(humanoid); };
	void AddTouchable(Pickup* pickup) { m_Touchables.emplace_back(pickup); };
};
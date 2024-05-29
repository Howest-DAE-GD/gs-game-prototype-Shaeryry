#pragma once
static const float WINDOW_WIDTH{ 846.f };
static const float WINDOW_HEIGHT{ 500.f };

static const float ATTACK_COOLDOWN{ 1 };

static const float BALL_MAX_SPEED{ 5000.f };
static const float BALL_SPEED_INCREASE{ 5.f };
static const float BALL_ATTACK_RANGE{ 60 };
static const float DEFAULT_BALL_SPEED{ 50 };
static const float DEFAULT_BALL_RADIUS{ 15.f };

static const float DEFAULT_HUMANOID_MOVEMENT_SPEED{ 300 }; 
static const float DEFAULT_HUMANOID_JUMP_POWER{ 900 };
static const float DEFAULT_HUMANOID_ACCELERATION{ 400 };
static const float DEFAULT_HUMANOID_DECELERATION{ 300 };

static const float ENEMY_REACTION_OFFSET{ (BALL_ATTACK_RANGE) };
static const float ENEMY_REACTION_RANGE{ 50 };

static const SDL_Keycode FORWARD_KEY{ SDLK_UP };
static const SDL_Keycode LEFT_KEY{ SDLK_LEFT };
static const SDL_Keycode RIGHT_KEY{ SDLK_RIGHT };
static const SDL_Keycode DOWN_KEY{ SDLK_DOWN };	


// new 

static const float GRAVITY{ 9.81f };
static const float GROUND_HEIGHT{ 50 };
static const float BOSS_OFFSET{ 350 };

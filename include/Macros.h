#pragma once
#include <SFML/Graphics.hpp>

//button
const sf::Vector2f BUTTON_SIZE = { 250.f, 200.f };
const sf::Vector2f SCALE_BUTTON = { 1.f, 0.4f };
const sf::Vector2f HOVERD = { 260.f, 210.f };
const sf::Vector2f BOARD_BUTTON_SIZE = { 50.f, 50.f };
const sf::Vector2f SCALE_B = { 0.4f, 0.4f };

//controller
const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 800;
const int BOARD_WIDTH = 15000;
const int BOARD_HEIGHT = 1002;
const sf::Vector2f START_POINT = { 0.f,0.f };

//directions
const sf::Vector2f UP = { 0 , -1 };
const sf::Vector2f DOWN = { 0 , 1 };
const sf::Vector2f RIGHT = { 1 , 0 };
const sf::Vector2f LEFT = { -1 , 0 };

//menu
const float MENU_POS_X = 600.f;
const float MENU_POS_Y = 300.f;
const sf::Vector2f MUSIC_BUTTON_POS = { 50.f, 50.f };

//Board
const sf::Vector2f BAR_SIZE = { 500.f, 100.f };
const sf::Vector2f BAR_POSITION = { 170.f, 30.f};

const int REQUIRED_BIG_FISH = 8;
const int REQUIRED_MEDIUM_FISH = 9;
const int REQUIRED_SMALL_FISH = 50;
const int REQUIRED_SHARKS = 4;
const int REQUIRED_BOTTLES = 11;
const int REQUIRED_CORALS = 4;
const int REQUIRED_STONES = 23;
const int REQUIRED_KEYS = 5;
const int REQUIRED_ANCHOR = 2;
const int REQUIRED_JELLY_FISH = 3;
const int REQUIRED_TREASURE = 1;
const int REQUIRED_BUBBLES = 2;
const int REQUIRED_FISH_HOOK = 1;
const int REQUIRED_SHELL = 2;

//moving objects
const float ELAPSED = 0.0f;
const float MOVE_DURATION = 2.0f;
const int CURRENT_FRAME = 0;
const float FRAME_DURATION = 0.1f;
const sf::Vector2f LEFT_SCALE = { -1.f, 1.f };
const sf::Vector2f RIGHT_SCALE = { 1.f, 1.f };

//other fish
const float MAX_DISTANCE = 500.f;
const sf::Vector2f LEFT_DIRECTION = { -1.f, 0.f };
const sf::Vector2f RIGHT_DIRECTION = { 1.f, 0.f };
const sf::Vector2f UP_DIRECTION = { 0.f, -1.f };
const sf::Vector2f DOWN_DIRECTION = { 0.f, 1.f };
const sf::Vector2f FREEZE = { 0.f,0.f };

//help screen
const int HELP_WIDTH = 1063;
const int HELP_HEIGHT = 597;

//PlayCommand
const sf::Vector2f FISH_START_POS = sf::Vector2f(100.f, 350.f);
const sf::Vector2f HOME_BUTTON_P = { 20.f, 20.f };
const sf::Vector2f PAUSE_BUTTON_P = { 20.f, 110.f };
const sf::Vector2f MUSIC_BUTTON_P = { 20.f, 200.f };
const sf::Vector2f START_POS = { 0.f, 0.f };

//Fish
const sf::Vector2f FISH_INIT_SIZE = { 80.f, 80.f };
const int FISH_LIFE = 3;
const int INIT_SCORE = 0;
const int INIT_KEYS = 0;
const sf::Vector2f INIT_DIRECTION = { 0.0f, 0.0f };
const float MOVEMENT_SPEED = 400.f;
const float CRAZY_SPEED = 500.f;
const sf::Vector2f SCORE_DATA_POS = { 210.f, 40.f };
const sf::Vector2f LIFE_DATA_POS = { 370.f, 40.f };
const sf::Vector2f KEYS_DATA_POS = { 530.f, 40.f };

//music
const int VOLUME = 50;
enum Sounds
{
	EAT_SOUND,
	COLLECT_SOUND,
	GROWTH_SOUND,
	WIN_SOUND,
	GAME_OVER_SOUND,
	SMALL_SIZE_SOUND
};

//collisions
const float SMALL_RESIZE = 10.f;
const float BIG_RESIZE = 20.f;
const float MAX_FISH_SIZE = 220.f;

//anchor
const sf::Vector2f ANCHOR_POSITION = { 2300.0f, 600.0f };
const sf::Vector2f ANCHOR_SIZE = { 350.0f, 400.0f };

//big fish
const sf::Vector2f BIG_FISH_SIZE = { 250.f, 220.f };
const float BIG_FISH_SPEED = 180.f;

//medium fish
const sf::Vector2f MEDIUM_FISH_SIZE = { 200.f, 200.f };
const float MEDIUM_FISH_SPEED = 200.f;

//small fish
const sf::Vector2f SMALL_FISH_SIZE = { 50.f, 50.f };
const float SMALL_FISH_SPEED = 130.f;

//botlle
const sf::Vector2f BOTTLE_SIZE = { 120.f, 120.f };

//bubble
const sf::Vector2f BUBBLE_SIZE = { 120.f, 150.f };

//coral
const sf::Vector2f CORAL_SIZE = { 100.f, 100.f };

//stone
const sf::Vector2f STONE_SIZE = { 100.f, 100.f };

//treasure
const sf::Vector2f TREASURE_SIZE = { 150.f, 150.f };
const sf::Vector2f TREASURE_POSITION = { 14800.0f, 820.0f };

//shark
const sf::Vector2f SHARK_SIZE = { 500.f, 300.f };
const float SHARK_SPEED = 130.f;

//fish hook
const sf::Vector2f HOOK_START_POS = sf::Vector2f(700.f, -250.f);
const sf::Vector2f HOOK_SIZE = { 200.f, 400.f };
const int HOOK_FALLS_COUNT = 0;
const int MAX_HOOK_FALLS = 4;
const float HOOK_X_OFFSET = 0.0f;
const float HOOK_FALL_DURATION = 4.0f;
const float HOOK_Y_OFFSET = 300.0f;
const float OFFSET = 3000.0f;

//jelly fish
const sf::Vector2f JELLY_FISH_SIZE = { 80.f, 80.f };
const float JELLY_FISH_SPEED = 220.f;

//Key
const sf::Vector2f KEY_SIZE = { 100.f, 100.f };

//shell
const sf::Vector2f SHELL_SIZE = { 100.f, 100.f };

//crazy fish
const int CRAZY_TIME = 5;
const sf::Vector2f NORMAL_FISH_SIZE = { 100.f, 100.f };
const sf::Vector2f CRAZY_FISH_SIZE = { 300.f, 300.f };
const sf::Vector2f CRAZY_FISH_SPEED = { 500.f, 500.f };

//protected fish
const float PROTECTION_DURATION = 15.0f;

//bar
const int TEXT_SIZE = 50;




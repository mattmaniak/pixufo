#include "sdlwrap.hpp"
#include "window.hpp"
#include "game.hpp"

Game::Game()
{
	running = true;
}

Game::~Game()
{
	quit();
}

void Game::handle_keyboard()
{
	// const Uint8* pressed_key = SDL_GetKeyboardState(nullptr);
	//
	// SDL_PollEvent(event);
	// switch(event.type) // TODO: SLASH SPEED - DIVIDE BY 2^(1/2).
	// {
	// 	case SDL_QUIT:
	// 	running = false;
	// 	break;
	//
	// 	case SDL_KEYDOWN:
	// 	case SDL_KEYUP:
	// 	if(pressed_key[SDL_SCANCODE_UP])
	// 	{
	// 		if(Player.y >= Player.step)
	// 		{
	// 			Player.y -= Player.step;
	// 		}
	// 	}
	// 	if(pressed_key[SDL_SCANCODE_DOWN])
	// 	{
	// 		if((Player.y + Player.Geometry.h + Player.step) <= Window.Desktop.h)
	// 		{
	// 			Player.y += Player.step;
	// 		}
	// 	}
	// 	if(pressed_key[SDL_SCANCODE_LEFT])
	// 	{
	// 		if(Player.x >= Player.step)
	// 		{
	// 			Player.x -= Player.step;
	// 		}
	// 	}
	// 	if(pressed_key[SDL_SCANCODE_RIGHT])
	// 	{
	// 		if((Player.x + Player.Geometry.w + Player.step) <= Window.Desktop.w)
	// 		{
	// 			Player.x += Player.step;
	// 		}
	// 	}
	// }
}

void Game::loop()
{
	// TODO
}

void Game::quit()
{
	SDL_Quit();
}

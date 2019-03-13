#include "pixufo.hpp"

// Very ugly SDL2 error fix: "undefined reference to WinMain".
#ifdef main
#undef main
#endif

Game::Game()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2 module.");
		throw std::runtime_error("");
	}
	if(TTF_Init() != SDL2_SUCCESS)
	{
		error::show_box("Can't initialize the SDL2 true type fonts module.");
		throw std::runtime_error("");
	}
	Graphics_ = new Graphics;
	Menus_     = new Menus(*Graphics_);
	Keyboard_ = new Keyboard;
	Cosmic_   = new Level(*Graphics_, "background_level", 2);
}

Game::~Game()
{
	delete Graphics_;
	delete Cosmic_;
	delete Menus_;
	delete Keyboard_;

	TTF_Quit();
	SDL_Quit();
}

void Game::loop()
{
	for(;;)
	{
		if(!Graphics_->set_up_new_frame())
		{
			Cosmic_->set_entities_borders(*Graphics_);
		}
		if(Menus_->mode == Menus_->primary_enabled)
		{
			if(!Menus_->primary(*Graphics_, *Keyboard_))
			{
				return;
			}
			Cosmic_->reset();
			SDL_Delay(500);
			Graphics_->count_fps();
		}
		if(!Cosmic_->Ufo->keyboard_steering(*Menus_, *Graphics_))
		{
			return;
		}

		for(std::size_t idx = 0; idx < Cosmic_->Enemies.size(); idx++)
		{
			Cosmic_->check_entity_pos(*Cosmic_->Enemies[idx]);
		}
		Cosmic_->check_entity_pos(*Cosmic_->Ufo);

		if(Cosmic_->check_player_collision(*Graphics_))
		{
			SDL_Delay(2000);
			return;
		}
		if(!Cosmic_->render(*Graphics_))
		{
			return;
		}
		if(Menus_->mode == Menus_->pause_enabled)
		{
			SDL_Delay(500);
			if(!Menus_->pause(*Graphics_, *Keyboard_, *Cosmic_))
			{
				return;
			}
			SDL_Delay(500);
		}
		if(!Graphics_->count_fps())
		{
			return;
		}
	}
}

int main()
{
	try
	{
		Game Pixufo;
		Pixufo.loop();
	}
	catch(...) {}
}

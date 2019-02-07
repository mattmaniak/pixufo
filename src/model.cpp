#include "model.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"

Model::Model(Graphics* Graphics, const std::string name,
             const float passed_speed): speed(passed_speed)
{
	Texture = Graphics->load_texture(name);
	if(Texture == nullptr)
	{
		initialized = false;
		return;
	}

	if(SDL_QueryTexture(Texture, nullptr, nullptr, &Geometry.w, &Geometry.h)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get a texture size.");
		initialized = false;
		return;
	}

	Geometry.w *= pixelart_pixel_sz();
	Geometry.h *= pixelart_pixel_sz();
	Geometry.x  = pos_x = 0.0f;
	Geometry.y  = pos_y = 0.0f;

	min_x = max_x = min_y = max_y = 0; // Reanitialized in derived models.

	step = 0.0f;

	initialized = true;
}

Model::~Model()
{
	if(Texture != nullptr)
	{
		SDL_DestroyTexture(Texture);
	}
}

float Model::pixelart_pixel_sz()
{
	const int       display_idx = 0;
	SDL_DisplayMode Ingame_display;

	if(SDL_GetDesktopDisplayMode(display_idx, &Ingame_display)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get the current display size.");
		initialized = false;
	}
	return Ingame_display.w / PIXELART_DISPLAY_WIDTH;
}

Button::Button(Graphics* Graphics, const std::string name,
                      const int idx):
Model(Graphics, name, 0.0f), idx(idx)
{

}

bool Button::render(Graphics* Graphics, unsigned int current_idx)
{
	const unsigned int current_button_shift = 64;

	// Centering.
	Geometry.x = (Graphics->Screen.w - Geometry.w) / 2;
	Geometry.y = (Graphics->Screen.h / 2) + (idx * Geometry.h);

	// Selected button shift.
	if(idx == current_idx)
	{
		Geometry.x += current_button_shift;
	}
	if(SDL_RenderCopy(Graphics->Renderer, Texture, NULL, &Geometry)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't copy a texture to the renderer.");
		return false;
	}
	return true;
}

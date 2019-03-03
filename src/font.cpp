#include "font.hpp"

Font::Font(Graphics& Graphics, const std::string passed_text,
           const int passed_sz): name(FONTNAME), text(passed_text),
           sz(passed_sz)
{
	const std::string directory = "font";
	const std::string path      = directory + SEPARATOR + name;

	is_initialized = false;

	Font_ttf = TTF_OpenFont(path.c_str(), sz);
	if(Font_ttf == nullptr)
	{
		error::show_box("Can't load the font: " + path);
		return;
	}
	Color.r = 120;
	Color.g = 244;
	Color.b = 004;

	// Blended - high quality, Solid - low quality.
	SDL_Surface* Surface = TTF_RenderUTF8_Blended(Font_ttf, text.c_str(), Color);
	if(Surface == nullptr)
	{
		error::show_box("Can't create the surface from the font: " + path);
		return;
	}
	TTF_CloseFont(Font_ttf);

	Texture = SDL_CreateTextureFromSurface(Graphics.Renderer, Surface);
	if(Texture == nullptr)
	{
		error::show_box("Can't create the texture from the font: " + path);
		return;
	}
	SDL_FreeSurface(Surface);

	if(SDL_QueryTexture(Texture, nullptr, nullptr, &Geometry.w, &Geometry.h)
	  != SDL2_SUCCESS)
	{
		error::show_box("Can't get the size of the texture: " + name);
		return;
	}
	Geometry.w *= Graphics.pixelart_px_sz;
	Geometry.h *= Graphics.pixelart_px_sz;

	is_initialized = true;
}

Font::~Font()
{
	SDL_DestroyTexture(Texture);
}

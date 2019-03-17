#include "font.hpp"

Font::Font(Graphics& Graphics, const std::string passed_text,
           const unsigned int passed_sz): name(FONTNAME), text(passed_text),
           sz(passed_sz * Graphics.pixelart_px_sz)
{
	const std::string path = FONT_PATH + SEPARATOR + name;
	SDL_Surface*      Surface;

	Font_ttf = TTF_OpenFont(path.c_str(), sz);
	if(Font_ttf == nullptr)
	{
		throw error::Exception_box("Can't load the font: " + path);
	}
	Color.r = 120;
	Color.g = 244;
	Color.b = 004;

	// Blended - high quality, Solid - low quality.
	Surface = TTF_RenderUTF8_Blended(Font_ttf, text.c_str(), Color);
	if(Surface == nullptr)
	{
		throw error::Exception_box("Can't create the surface from the font: "
		                           + path);
	}
	TTF_CloseFont(Font_ttf);

	Texture = SDL_CreateTextureFromSurface(Graphics.Renderer, Surface);
	if(Texture == nullptr)
	{
		throw error::Exception_box("Can't create the texture from the font: "
		                           + path);
	}
	SDL_FreeSurface(Surface);

	if(SDL_QueryTexture(Texture, nullptr, nullptr, &Geometry.w, &Geometry.h)
	  != SDL2_SUCCESS)
	{
		throw error::Exception_box("Can't get the size of the texture: "
		                           + name);
	}
}

Font::~Font()
{
	SDL_DestroyTexture(Texture);
}

bool Font::render(Graphics& Graphics)
{
	Geometry.x = pos_x;
	Geometry.y = pos_y;

	if(SDL_RenderCopy(Graphics.Renderer, Texture, nullptr, &Geometry)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't copy the texture: " + name
		                + " to the renderer.");
		return false;
	}
	return true;
}

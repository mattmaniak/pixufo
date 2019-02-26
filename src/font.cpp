#include "font.hpp"

Font::Font(Graphics& Graphics, const std::string passed_text,
           const int passed_sz): name(FONTNAME), text(passed_text),
           sz(passed_sz)
{
	const std::string directory = "font";

#ifdef _WIN32
	const std::string separator = "\\";

#else
#ifdef __linux__
	const std::string separator = "/";
#endif

#endif

	const std::string path = directory + separator + name;

	Font_ttf = TTF_OpenFont(path.c_str(), sz);
	if(Font_ttf == nullptr)
	{
		error::show_box("Can't load the font: " + path);
		is_initialized = false;
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
		is_initialized = false;
		return;
	}
	TTF_CloseFont(Font_ttf);

	Texture = SDL_CreateTextureFromSurface(Graphics.Renderer, Surface);
	if(Texture == nullptr)
	{
		error::show_box("Can't create the texture from the font: " + path);
		is_initialized = false;
		return;
	}
	SDL_FreeSurface(Surface);

	if(SDL_QueryTexture(Texture, nullptr, nullptr, &Geometry.w, &Geometry.h)
	  != SDL2_SUCCESS)
	{
		error::show_box("Can't get the size of the texture: " + name);
		is_initialized = false;
		return;
	}
	is_initialized = true;
}

Font::~Font()
{
	SDL_DestroyTexture(Texture);
}

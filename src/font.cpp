#include "font.hpp"

Font::Font(Graphics& Graphics, const std::string passed_text,
           const unsigned int passed_size):
           size(passed_size * Graphics.pixelart_px_sz), name_(FONTNAME),
           text_(passed_text)
{
    const std::string path = FONT_PATH + SEPARATOR + name_;
    SDL_Surface*      Surface;

    Font_ = TTF_OpenFont(path.c_str(), size);
    if(Font_ == nullptr)
    {
        throw error::Exception_box("Can't load the font: " + path);
    }
    Color_.r = 120;
    Color_.g = 244;
    Color_.b = 004;

    // Blended - high quality, Solid - low quality.
    Surface = TTF_RenderUTF8_Blended(Font_, text_.c_str(), Color_);
    if(Surface == nullptr)
    {
        throw error::Exception_box("Can't create the surface from the font: "
                                   + path);
    }
    TTF_CloseFont(Font_);

    Texture_ = SDL_CreateTextureFromSurface(Graphics.Renderer, Surface);
    if(Texture_ == nullptr)
    {
        throw error::Exception_box("Can't create the text_ure from the font: "
                                   + path);
    }
    SDL_FreeSurface(Surface);

    if(SDL_QueryTexture(Texture_, nullptr, nullptr, &Geometry.w, &Geometry.h)
      != SDL2_SUCCESS)
    {
        throw error::Exception_box("Can't get the size of the text_ure: "
                                   + name_);
    }
}

Font::~Font()
{
    SDL_DestroyTexture(Texture_);
}

bool Font::render(Graphics& Graphics)
{
    Geometry.x = pos_x;
    Geometry.y = pos_y;

    if(SDL_RenderCopy(Graphics.Renderer, Texture_, nullptr, &Geometry)
       != SDL2_SUCCESS)
    {
        error::show_box("Can't copy the text_ure: " + name_
                        + " to the renderer.");
        return false;
    }
    return true;
}

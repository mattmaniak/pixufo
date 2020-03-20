#include "sprite.hpp"

Sprite::Sprite(Graphics& graphics, const std::string passed_name,
               const Uint32 passed_single_frame_time_ms):
               name(passed_name), current_frame_idx(0),
               current_frame_start_time_ms_(passed_single_frame_time_ms)
{
    if(!load_textures_(graphics))
    {
        throw std::runtime_error("");
    }

    /* As there is only the first texture size check, trying to load animation
    with various texture sizes may brake it's rendering. */
    if(SDL_QueryTexture(textures[current_frame_idx], nullptr, nullptr,
       &geometry.w, &geometry.h) != SDL2_SUCCESS)
    {
        throw error::Exception_box("Can't get the size of the texture: "
                                   + name);
    }
    pos_x = 0.0;
    pos_y = 0.0;

    geometry.w *= graphics.pixelart_px_sz;
    geometry.h *= graphics.pixelart_px_sz;
}

Sprite::~Sprite()
{
    if(current_frame_start_time_ms_ == 0)
    {
        SDL_DestroyTexture(textures[current_frame_start_time_ms_]);
    }
    else
    {
        for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
        {
            SDL_DestroyTexture(textures[idx]);
        }
    }
}

void Sprite::move(Graphics& graphics, const double offset_x,
                  const double offset_y)
{
    pos_x += offset_x * graphics.delta_time_s * graphics.pixelart_px_sz;
    pos_y += offset_y * graphics.delta_time_s * graphics.pixelart_px_sz;
}

void Sprite::animate(const Graphics& graphics)
{
    if(current_frame_start_time_ms_ > 0)
    {
        current_frame_elapsed_time_ms_ += graphics.delta_time_s * 1000.0;

        if(current_frame_elapsed_time_ms_ >= current_frame_start_time_ms_)
        {
            current_frame_elapsed_time_ms_ = 0;
            current_frame_idx++;
        }
        if(current_frame_idx >= FRAMES_AMOUNT)
        {
            current_frame_idx = 0;
        }
    }
}

bool Sprite::render(Graphics& graphics)
{
    animate(graphics);

    geometry.x = pos_x;
    geometry.y = pos_y;

    if(SDL_RenderCopy(graphics.renderer, textures[current_frame_idx], nullptr,
       &geometry) != SDL2_SUCCESS)
    {
        error::show_box("Can't render the: " + name);
        return false;
    }
    return true;
}

bool Sprite::load_textures_(Graphics& graphics)
{
    SDL_Surface* Image;
    std::string  path;

    if(current_frame_start_time_ms_ == 0) // No animation.
    {
        path = TEXTURES_PATH + name + IMAGE_EXTENSION;

        Image = SDL_LoadBMP(path.c_str());
        if(Image == nullptr)
        {
            return false;
        }
        textures[current_frame_idx] =
        SDL_CreateTextureFromSurface(graphics.renderer, Image);

        if(textures[current_frame_idx] == nullptr)
        {
            error::show_box("Can't create the texture from the image: " + name);
            return false;
        }
        SDL_FreeSurface(Image);
    }
    else // Dir with animations.
    {
        for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
        {
            path = TEXTURES_PATH + name + SEPARATOR + std::to_string(idx)
                   + IMAGE_EXTENSION;

            Image = SDL_LoadBMP(path.c_str());
            if(Image == nullptr)
            {
                return false;
            }
            textures[idx] = SDL_CreateTextureFromSurface(graphics.renderer,
                                                         Image);
            if(textures[idx] == nullptr)
            {
                return false;
            }
            SDL_FreeSurface(Image);
        }
    }
    return true;
}

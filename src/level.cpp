#include "level.hpp"

Level::Level(Graphics& Graphics, const std::string bg_name,
             const unsigned int passed_nebulas_amount):
Scene(Graphics, bg_name), nebulas_amount_(passed_nebulas_amount)
{
    const double size_to_screen_width_ratio = 1.0;

    width  = Graphics.Display.w * size_to_screen_width_ratio;
    height = Graphics.Display.h * size_to_screen_width_ratio;

    try
    {
        Ufo = new Player(Graphics);
    }
    catch(...)
    {
        throw std::runtime_error("");
    }
    set_nebulas_borders_(Graphics, *Ufo);

    // Set the player's default position;
    Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w)  / 2;
    Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

    randomize_nebulas_amount_();

    for(std::size_t idx = 0; idx < nebulas_amount_; idx++) // Create all enemies.
    {
        try
        {
            randomize_nebula_type_(Graphics);
        }
        catch(...)
        {
            throw std::runtime_error("");
        }
        set_nebulas_borders_(Graphics, *Nebulas_[idx]);
    }
}

Level::~Level()
{
    for(auto& Nebula: Nebulas_)
    {
        delete Nebula;
    }
    delete Ufo;
}

void Level::reset()
{
    Ufo->Movements["horizontal"]->keypress_time_s = 0.0;
    Ufo->Movements["vertical"]->keypress_time_s   = 0.0;

    Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w)  / 2;
    Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

    // randomize_nebulas_pos_();

    for(auto& Nebula: Nebulas_)
    {
        Nebula->randomize_initial_pos();
    }
    score_points = 0;
}

void Level::set_nebulas_borders(Graphics& Graphics)
{
    width  = Graphics.Display.w;
    height = Graphics.Display.h;

    for(auto& Nebula: Nebulas_)
    {
        set_nebulas_borders_(Graphics, *Nebula);
    }
    set_nebulas_borders_(Graphics, *Ufo);
}

void Level::check_ufo_pos()
{
    // If the model is out of the level, it will be moved to the mirrored place.
    if(Ufo->pos_x < Ufo->min_x)
    {
        Ufo->pos_x = Ufo->max_x;
    }
    else if(Ufo->pos_x > Ufo->max_x)
    {
        Ufo->pos_x = Ufo->min_x;
    }
    else if(Ufo->pos_y < Ufo->min_y)
    {
        Ufo->pos_y = Ufo->max_y;
    }
    else if(Ufo->pos_y > Ufo->max_y)
    {
        Ufo->pos_y = Ufo->min_y;
    }
}

bool Level::check_ufo_collision()
{
    for(std::size_t en_idx = 0; en_idx < Nebulas_.size(); en_idx++)
    {
        if(SDL_HasIntersection(&Ufo->Geometry, &Nebulas_[en_idx]->Geometry))
        {
            if(check_advanced_ufo_collision_(en_idx))
            {
                return true;
            }
        }
    }
    return false;
}

void Level::check_nebulas_pos(Graphics& Graphics)
{
    for(auto& Nebula: Nebulas_)
    {
        if((Nebula->pos_x < Nebula->min_x) || (Nebula->pos_x > Nebula->max_x))
        {
            Nebula->hidden_timeout_ms += Graphics.delta_time_s * 1000.0;
        }
        if(Nebula->hidden_timeout_ms > NEBULA_HIDDEN_TIMEOUT_MS)
        {
            Nebula->hidden_timeout_ms = 0;

            Nebula->randomize_initial_pos();
            Nebula->pos_x = Graphics.Display.w - Graphics.pixelart_px_sz;
        }
    }
}

bool Level::render(Graphics& Graphics)
{
    Font Score_font(Graphics, std::to_string(score_points), 30);
    Score_font.pos_x = Score_font.pos_y = PADDING / 2.0; // Left, upper corner.

    if(!Bg->tile_and_render(Graphics))
    {
        return false;
    }
    Bg->move(Graphics, -8.0, 0.0);

    for(auto& Nebula: Nebulas_)
    {
        if(!Nebula->render(Graphics))
        {
            return false;
        }
        Nebula->move(Graphics, -Nebula->max_speed, 0.0); // Moving to the left.
    }
    if(!Ufo->render(Graphics))
    {
        return false;
    }
    if(!Score_font.render(Graphics))
    {
        return false;
    }
    SDL_RenderPresent(Graphics.Renderer);

    return true;
}

void Level::set_nebulas_borders_(Graphics& Graphics, Entity& Entity)
{
    Entity.min_x = Graphics.pixelart_px_sz - Entity.Geometry.w;
    Entity.min_y = Graphics.pixelart_px_sz - Entity.Geometry.h;
    Entity.max_x = width  - Graphics.pixelart_px_sz;
    Entity.max_y = height - Graphics.pixelart_px_sz;
}


void Level::randomize_nebulas_amount_()
{
    std::mt19937 prng;
    prng.seed(std::random_device()());

    std::uniform_int_distribution<std::mt19937::result_type>
    distributor_nebulas(MIN_NEBULAS_AMOUNT, MAX_NEBULAS_AMOUNT);

    nebulas_amount_ = distributor_nebulas(prng);
}

void Level::randomize_nebula_type_(Graphics& Graphics)
{
    const int nebulas_type_pool = 10;

    std::mt19937 prng;
    prng.seed(std::random_device()());

    std::uniform_int_distribution<>
    distributor_nebula_type(0, nebulas_type_pool - 1);

    try
    {
        switch(distributor_nebula_type(prng))
        {
        case 0:
        case 1:
        case 2:
        case 3:
            Nebulas_.push_back(new Entity(Graphics, "nebula_wasp", 160.0, 80));
            break;

        case 4:
        case 5:
        case 6:
            Nebulas_.push_back(new Entity(Graphics, "nebula_medium", 120.0,
                                         100));
            break;

        case 7:
        case 8:
            Nebulas_.push_back(new Entity(Graphics, "nebula_big", 90.0, 160));
            break;

        case 9:
            Nebulas_.push_back(new Entity(Graphics, "nebula_umbrella", 50.0,
                                         200));
        }
    }
    catch(...)
    {
        std::runtime_error("");
    }
}

bool Level::check_advanced_ufo_collision_(const std::size_t en_idx)
{
    SDL_Rect Player_hbox_part;
    SDL_Rect Nebula_hbox_part;

    // Check the Player's hitbox part by Nebulas_' hitbox part.
    for(std::size_t pl_hb_idx = 0; pl_hb_idx < Ufo->Hitbox_parts.size();
        pl_hb_idx++)
    {
        // Position the Player's hitbox part.
        Player_hbox_part.w = Ufo->Hitbox_parts[pl_hb_idx].w;
        Player_hbox_part.h = Ufo->Hitbox_parts[pl_hb_idx].h;
        Player_hbox_part.x = Ufo->pos_x + (Ufo->Hitbox_parts[pl_hb_idx].x);
        Player_hbox_part.y = Ufo->pos_y + (Ufo->Hitbox_parts[pl_hb_idx].y);

        for(std::size_t en_hb_idx = 0;
            en_hb_idx < Nebulas_[en_idx]->Hitbox_parts.size(); en_hb_idx++)
        {
            // Position the Nebula's hitbox part.
            Nebula_hbox_part.w = Nebulas_[en_idx]->Hitbox_parts[en_hb_idx].w;
            Nebula_hbox_part.h = Nebulas_[en_idx]->Hitbox_parts[en_hb_idx].h;
            Nebula_hbox_part.x = Nebulas_[en_idx]->pos_x
                                + (Nebulas_[en_idx]->Hitbox_parts[en_hb_idx].x);

            Nebula_hbox_part.y = Nebulas_[en_idx]->pos_y
                                + (Nebulas_[en_idx]->Hitbox_parts[en_hb_idx].y);

            if(SDL_HasIntersection(&Player_hbox_part, &Nebula_hbox_part))
            {
                return true; // Collision.
            }
        }
    }
    return false;
}

void Level::randomize_nebulas_pos_() // Causes infinite loop...
{
    for(std::size_t idx = 0; idx < Nebulas_.size() - 1; idx++)
    {
        while((Nebulas_[idx]->Geometry.x == Nebulas_[idx + 1]->Geometry.x)
              || (Nebulas_[idx]->Geometry.y == Nebulas_[idx + 1]->Geometry.y))
        {
            Nebulas_[idx]->randomize_initial_pos();
        }
    }
}

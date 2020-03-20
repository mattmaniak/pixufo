#include "level.hpp"

Level::Level(Graphics& graphics, const std::string bg_name,
             const unsigned int enemies_number):
Scene(graphics, bg_name), _enemies_number(enemies_number)
{
    const double size_to_screen_width_ratio = 1.0;

    _width  = graphics.Display.w * size_to_screen_width_ratio;
    _height = graphics.Display.h * size_to_screen_width_ratio;

    try
    {
        Ufo = new Player(graphics);
    }
    catch(...)
    {
        throw std::runtime_error("");
    }
    _adjust_enemies_border(graphics, *Ufo);

    // Set the player's default position;
    Ufo->geometry.x = Ufo->pos_x = (_width - Ufo->geometry.w)  / 2;
    Ufo->geometry.y = Ufo->pos_y = (_height - Ufo->geometry.h) / 2;

    randomize_enemies_amount_();

    for(std::size_t idx = 0; idx < _enemies_number; idx++) // Create all enemies.
    {
        try
        {
            randomize_enemy_type_(graphics);
        }
        catch(...)
        {
            throw std::runtime_error("");
        }
        _adjust_enemies_border(graphics, *_enemies[idx]);
    }
}

Level::~Level()
{
    for(auto& Nebula: _enemies)
    {
        delete Nebula;
    }
    delete Ufo;
}

void Level::reset()
{
    Ufo->Movements["horizontal"]->keypress_time_s = 0.0;
    Ufo->Movements["vertical"]->keypress_time_s   = 0.0;

    Ufo->geometry.x = Ufo->pos_x = (_width - Ufo->geometry.w)  / 2;
    Ufo->geometry.y = Ufo->pos_y = (_height - Ufo->geometry.h) / 2;

    // randomize_enemies_pos_();

    for(auto& Nebula: _enemies)
    {
        Nebula->randomize_initial_pos();
    }
    score_points = 0;
}

void Level::adjust_enemy_border(Graphics& graphics)
{
    _width  = graphics.Display.w;
    _height = graphics.Display.h;

    for(auto& Nebula: _enemies)
    {
        _adjust_enemies_border(graphics, *Nebula);
    }
    _adjust_enemies_border(graphics, *Ufo);
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
    for(std::size_t en_idx = 0; en_idx < _enemies.size(); en_idx++)
    {
        if(SDL_HasIntersection(&Ufo->geometry, &_enemies[en_idx]->geometry))
        {
            if(check_advanced_ufo_collision_(en_idx))
            {
                return true;
            }
        }
    }
    return false;
}

void Level::check_enemies_pos(Graphics& graphics)
{
    for(auto& Nebula: _enemies)
    {
        if((Nebula->pos_x < Nebula->min_x) || (Nebula->pos_x > Nebula->max_x))
        {
            Nebula->hidden_timeout_ms += graphics.delta_time_s * 1000.0;
        }
        if(Nebula->hidden_timeout_ms > NEBULA_HIDDEN_TIMEOUT_MS)
        {
            Nebula->hidden_timeout_ms = 0;

            Nebula->randomize_initial_pos();
            Nebula->pos_x = graphics.Display.w - graphics.pixelart_px_sz;
        }
    }
}

bool Level::render(Graphics& graphics)
{
    Font Score_font(graphics, std::to_string(score_points), 30);
    Score_font.pos_x = Score_font.pos_y = PADDING / 2.0; // Left, upper corner.

    if(!Bg->tile_and_render(graphics))
    {
        return false;
    }
    Bg->move(graphics, -8.0, 0.0);

    for(auto& Nebula: _enemies)
    {
        if(!Nebula->render(graphics))
        {
            return false;
        }
        Nebula->move(graphics, -Nebula->max_speed, 0.0); // Moving to the left.
    }
    if(!Ufo->render(graphics))
    {
        return false;
    }
    if(!Score_font.render(graphics))
    {
        return false;
    }
    SDL_RenderPresent(graphics.renderer);

    return true;
}

void Level::_adjust_enemies_border(Graphics& graphics, Entity& Entity)
{
    Entity.min_x = graphics.pixelart_px_sz - Entity.geometry.w;
    Entity.min_y = graphics.pixelart_px_sz - Entity.geometry.h;
    Entity.max_x = _width  - graphics.pixelart_px_sz;
    Entity.max_y = _height - graphics.pixelart_px_sz;
}


void Level::randomize_enemies_amount_()
{
    std::mt19937 prng;
    prng.seed(std::random_device()());

    std::uniform_int_distribution<std::mt19937::result_type>
    distributor_enemies(MIN_NEBULAS_AMOUNT, MAX_NEBULAS_AMOUNT);

    _enemies_number = distributor_enemies(prng);
}

void Level::randomize_enemy_type_(Graphics& graphics)
{
    const int enemies_type_pool = 10;

    std::mt19937 prng;
    prng.seed(std::random_device()());

    std::uniform_int_distribution<>
    distributor_enemy_type(0, enemies_type_pool - 1);

    try
    {
        switch(distributor_enemy_type(prng))
        {
        case 0:
        case 1:
        case 2:
        case 3:
            _enemies.push_back(new Entity(graphics, "enemy_wasp", 160.0, 80));
            break;

        case 4:
        case 5:
        case 6:
            _enemies.push_back(new Entity(graphics, "enemy_medium", 120.0,
                                         100));
            break;

        case 7:
        case 8:
            _enemies.push_back(new Entity(graphics, "enemy_big", 90.0, 160));
            break;

        case 9:
            _enemies.push_back(new Entity(graphics, "enemy_umbrella", 50.0,
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

    // Check the Player's hitbox part by _enemies' hitbox part.
    for(std::size_t pl_hb_idx = 0; pl_hb_idx < Ufo->hitbox_parts.size();
        pl_hb_idx++)
    {
        // Position the Player's hitbox part.
        Player_hbox_part.w = Ufo->hitbox_parts[pl_hb_idx].w;
        Player_hbox_part.h = Ufo->hitbox_parts[pl_hb_idx].h;
        Player_hbox_part.x = Ufo->pos_x + (Ufo->hitbox_parts[pl_hb_idx].x);
        Player_hbox_part.y = Ufo->pos_y + (Ufo->hitbox_parts[pl_hb_idx].y);

        for(std::size_t en_hb_idx = 0;
            en_hb_idx < _enemies[en_idx]->hitbox_parts.size(); en_hb_idx++)
        {
            // Position the Nebula's hitbox part.
            Nebula_hbox_part.w = _enemies[en_idx]->hitbox_parts[en_hb_idx].w;
            Nebula_hbox_part.h = _enemies[en_idx]->hitbox_parts[en_hb_idx].h;
            Nebula_hbox_part.x = _enemies[en_idx]->pos_x
                                + (_enemies[en_idx]->hitbox_parts[en_hb_idx].x);

            Nebula_hbox_part.y = _enemies[en_idx]->pos_y
                                + (_enemies[en_idx]->hitbox_parts[en_hb_idx].y);

            if(SDL_HasIntersection(&Player_hbox_part, &Nebula_hbox_part))
            {
                return true; // Collision.
            }
        }
    }
    return false;
}

void Level::randomize_enemies_pos_() // Causes infinite loop...
{
    for(std::size_t idx = 0; idx < _enemies.size() - 1; idx++)
    {
        while((_enemies[idx]->geometry.x == _enemies[idx + 1]->geometry.x)
              || (_enemies[idx]->geometry.y == _enemies[idx + 1]->geometry.y))
        {
            _enemies[idx]->randomize_initial_pos();
        }
    }
}

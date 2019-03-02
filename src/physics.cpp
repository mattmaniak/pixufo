#include "physics.hpp"

void physics::check_model_pos(Sprite& Sprite)
{
	// If the model is out of the level, it will be moved to the mirrored place.
	if(Sprite.pos_x < Sprite.min_x)
	{
		Sprite.pos_x = Sprite.max_x;
	}
	else if(Sprite.pos_x > Sprite.max_x)
	{
		Sprite.pos_x = Sprite.min_x;
	}
	else if(Sprite.pos_y < Sprite.min_y)
	{
		Sprite.pos_y = Sprite.max_y;
	}
	else if(Sprite.pos_y > Sprite.max_y)
	{
		Sprite.pos_y = Sprite.min_y;
	}
}

bool physics::check_player_collision(Graphics& Graphics, Level& Level)
{
	SDL_Rect Player_hbox_part;
	SDL_Rect Enemy_hbox_part;

	for(std::size_t en_idx = 0; en_idx < Level.Enemies.size(); en_idx++)
	{
		if(SDL_HasIntersection(&Level.Ufo->Geometry,
		                       &Level.Enemies[en_idx]->Geometry))
		{
			for(std::size_t pl_hb_idx = 0; pl_hb_idx < Level.Ufo->Hitbox_parts.size(); pl_hb_idx++)
			{
				Player_hbox_part.w = Level.Ufo->Hitbox_parts[pl_hb_idx].w * Graphics.pixelart_px_sz;
				Player_hbox_part.h = Level.Ufo->Hitbox_parts[pl_hb_idx].h * Graphics.pixelart_px_sz;
				Player_hbox_part.x = Level.Ufo->pos_x + (Level.Ufo->Hitbox_parts[pl_hb_idx].x * Graphics.pixelart_px_sz);
				Player_hbox_part.y = Level.Ufo->pos_y + (Level.Ufo->Hitbox_parts[pl_hb_idx].y * Graphics.pixelart_px_sz);

				for(std::size_t en_hb_idx = 0; en_hb_idx < Level.Enemies[en_idx]->Hitbox_parts.size(); en_hb_idx++)
				{
					Enemy_hbox_part.w = Level.Enemies[en_idx]->Hitbox_parts[en_hb_idx].w * Graphics.pixelart_px_sz;
					Enemy_hbox_part.h = Level.Enemies[en_idx]->Hitbox_parts[en_hb_idx].h * Graphics.pixelart_px_sz;
					Enemy_hbox_part.x = Level.Enemies[en_idx]->pos_x + (Level.Enemies[en_idx]->Hitbox_parts[en_hb_idx].x * Graphics.pixelart_px_sz);
					Enemy_hbox_part.y = Level.Enemies[en_idx]->pos_y + (Level.Enemies[en_idx]->Hitbox_parts[en_hb_idx].y * Graphics.pixelart_px_sz);

					if(SDL_HasIntersection(&Player_hbox_part, &Enemy_hbox_part))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

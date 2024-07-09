#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <limits>
#include "sprite.h"

class Background: public Sprite {
public:
    Background(Graphics&, std::string);

    bool tile_and_render(Graphics&); // Of course infinite.

private:
    void _scroll_endlessly();
};

#endif // BACKGROUND_H_

#include "graphics.hpp"
#include "error.hpp"

Graphics::Graphics()
{
	const int default_driver = -1;
	const int unused_size = 0;

	SDL_Surface* icon = load_image("icon");
	if(icon == nullptr)
	{
		error::show_box("Can't load the icon.");
		initialized = false;
		return;
	}
	if(SDL_GetDesktopDisplayMode(0, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the display size.");
		initialized = false;
		return;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_size, unused_size,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(Window == nullptr)
	{
		error::show_box("Can't create the window.");
		initialized = false;
		return;
	}
	if((Display.w < MIN_RESOLUTION_W) || (Display.h < MIN_RESOLUTION_H))
	{
		error::show_box("At least 1024x576 resolution is required.");
		initialized = false;
		return;
	}
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);

	Renderer = SDL_CreateRenderer(Window, default_driver,
	                              SDL_RENDERER_ACCELERATED
	                              | SDL_RENDERER_PRESENTVSYNC);
	if(Renderer == nullptr)
	{
		error::show_box("Can't create the renderer.");
		initialized = false;
		return;
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS)
	{
		error::show_box("Can't hide the mouse pointer.");
		initialized = false;
		return;
	}
	fps = 0;
	frame_elapsed_time = 0.0f;

	initialized = true;
}

Graphics::~Graphics()
{
	if(Renderer != nullptr)
	{
		SDL_DestroyRenderer(Renderer);
	}
	if(Window != nullptr)
	{
		SDL_DestroyWindow(Window);
	}
}

SDL_Texture* Graphics::load_texture(const std::string name)
{
	const std::string directory = "gfx";
	const std::string extension = "bmp";

#ifdef __linux__
	const std::string path = directory + '/' + name + '.' + extension;
#endif

#ifdef _WIN32
	const std::string path = directory + '\\' + name + '.' + extension;
#endif

	SDL_Surface* Image = SDL_LoadBMP(path.c_str());
	SDL_Texture* Texture;

	if(Image == nullptr)
	{
		error::show_box("Can't load the image: " + path);
		return nullptr;
	}

	Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	if(Texture == nullptr)
	{
		error::show_box("Can't create the texture from image: " + path);
	}
	SDL_FreeSurface(Image);

	return Texture;
}

bool Graphics::count_frame_start_time()
{
	if(SDL_GetTicks() >= std::numeric_limits<Uint32>::max())
	{
		error::show_box("The game can't run so long.");
		return false;
	}
	frame_start_time = SDL_GetTicks() / 1000.0f;

	return true;
}

bool Graphics::count_elapsed_time()
{
	fps++;

	if(fps >= std::numeric_limits<unsigned int>::max())
	{
		error::show_box("Too many frames per second.");
		return false;
	}
	if(SDL_GetTicks() >= std::numeric_limits<Uint32>::max())
	{
		error::show_box("The game can't run so long.");
		return false;
	}
	delta_time = ((SDL_GetTicks() / 1000.0f) - frame_start_time);

	if((frame_elapsed_time += delta_time) >= 1.0f)
	{
		fps = 0;
		frame_elapsed_time = 0.0f;
	}
	return true;
}

SDL_Surface* load_image(const std::string name)
{
	const std::string directory = "gfx";
	const std::string extension = "bmp";

#ifdef __linux__
	const std::string path = directory + '/' + name + '.' + extension;
#endif

#ifdef _WIN32
	const std::string path = directory + '\\' + name + '.' + extension;
#endif

	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	return image;
}

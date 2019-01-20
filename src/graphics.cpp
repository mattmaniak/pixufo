#include "graphics.hpp"

Graphics::Graphics()
{
	const int default_driver = -1;
	const int unused_size = 0;

	SDL_Surface* icon = load_image("icon");
	if(icon == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		initialized = false;
		return;
	}
	if(SDL_GetDesktopDisplayMode(0, &Display) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		initialized = false;
		return;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_size, unused_size,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(Window == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		initialized = false;
		return;
	}
	if((Display.w < MIN_RESOLUTION_W) || (Display.h < MIN_RESOLUTION_H))
	{
		std::cerr << "At least 1024x576 resolution is required." << std::endl;
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
		std::cerr << SDL_GetError() << std::endl;
		initialized = false;
		return;
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
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
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}

	Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	if(Texture == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(Image);

	return Texture;
}

void Graphics::count_frame_start_time()
{
	frame_start_time = SDL_GetTicks() / 1000.0f;
}

bool Graphics::count_elapsed_time()
{
	if(++fps >= std::numeric_limits<unsigned int>::max())
	{
		std::cerr << "Too many frames per second." << std::endl;
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

bool Graphics::render(void* Model_basic)
{
	// step = speed * Graphics->delta_time * count_scale();

	// if((Model_basic->Geometry.x > -Model_basic->Geometry.x)
	// && (Model_basic->Geometry.y > -Model_basic->Geometry.y)
	// && (Model_basic->Geometry.x < (Display.w + Model_basic->Geometry.x))
	// && (Model_basic->Geometry.y > (Display.h + Model_basic->Geometry.x)))
	// {
	// 	if(SDL_RenderCopy(Renderer, Model_basic->Texture, NULL, &Model_basic->Geometry) != 0)
	// 	{
	// 		std::cerr << SDL_GetError() << std::endl;
	// 		return false;
	// 	}
	// }
	return true;
}

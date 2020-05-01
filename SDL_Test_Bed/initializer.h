#pragma once



#include<SDL.h>



class Initializer
{
    static bool created_;

    bool sdl_init_success_{ false };
    const bool SDL_IMAGE_REQUESTED_;
    bool sdl_image_init_success_{ false };
    const bool SDL_TTF_REQUESTED_;
    bool sdl_ttf_init_success_{ false };

    SDL_Window* window_{ nullptr };
    SDL_Renderer* renderer_{ nullptr };

public:
    Initializer( bool image, bool ttf );//, std::optional<SDL_mixer_init_args> mixer );
    ~Initializer( void );

    SDL_Window* win( void );
    SDL_Renderer* renderer( void );
    bool good( void );
};


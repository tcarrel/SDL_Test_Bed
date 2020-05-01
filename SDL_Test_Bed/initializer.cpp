#include "input_handler.h"
#include "helper_funcs.h"
#include "initializer.h"



/*
TODO: Add initialization for these SDL extentions as well.
#include<SDL_mixer.h>
#include<SDL_net.h>
*/
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>



/// <summary>
/// We really only want one of these to be created.
/// </summary>
bool Initializer::created_{ false };



/// <summary>
/// Initializes
/// </summary>
/// <param name="image"></param>
/// <param name="ttf"></param>
Initializer::Initializer( bool image, bool ttf) //, std::optional<SDL_mixer_init_args> mixer )
    :
    SDL_IMAGE_REQUESTED_{ image },
    SDL_TTF_REQUESTED_{ ttf }
    //,SDL_MIXER_REQUESTED_{ mixer }
{
    if( !created_ )
    {
        created_ = true;
        
        if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        {
            std::cerr << "\tError:\n\tSDL could not be initialized.\n\t" << SDL_GetError() << '\n';
            return;
        }

        std::cerr << "\tSDL was initialized successfully.\n";
        sdl_init_success_ = true;

        window_ = SDL_CreateWindow(
            "SDL Test Bed",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1024, 768,
            SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN );

        if( !window_ )
        {
            std::cerr << "\tError:\n\tWindow could not be created.\n\t" << SDL_GetError() << '\n';
            return;
        }

        std::cerr << "\tWindow was created successfully.\n";

        renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED );

        if( !renderer_ )
        {
            std::cerr << "\tError:\n\tRenderer could not be created.\n\t" << SDL_GetError() << '\n';
            return;
        }

        SDL_SetRenderDrawColor( renderer_, 0, 89, 0, 0 );
        std::cerr << "\tRenderer was created successfully.\n";

        if( SDL_IMAGE_REQUESTED_ )
        {
            constexpr static const auto IMG_INIT_EVERYTHING{ IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP};
            if( IMG_Init( IMG_INIT_EVERYTHING ) != IMG_INIT_EVERYTHING )
            {
                std::cerr << "\tError:\n\tSDL_image failed to initialize all image formats.\n\t" << SDL_GetError() << '\n';
                return;
            }

            std::cerr << "\tSDL_image successfully initialized.\n";
            sdl_image_init_success_ = true;
        }

        if( SDL_TTF_REQUESTED_ )
        {
            if( TTF_Init() < 0 )
            {
                std::cerr << "\tError:\n\tSDL_ttf failed to initialize.\n\t" << SDL_GetError() << '\n';
                return;
            }

            std::cerr << "\tSDL_ttf successfully initialized.\n";
            sdl_ttf_init_success_ = true;
        }

        //if( mixer.has_value() )
        //{
        //    if( Mix_OpenAudio( mixer.value().frequency, mixer.value().format, mixer.value().channels, mixer.value().chunksize ) == -1 )
        //    {
        //        std::cerr << "\tError:\n\tSDL_mixer failed to initialize.\n\t" << SDL_GetError() << '\n';
        //        return;
        //    }

        //    std::cerr << "\tSDL_mixer successfully initialized.\n";
        //    sdl_mixer_init_success_ = true;
        //}
    }
}



Initializer::~Initializer( void )
{
    if( created_ )
    {
        if( SDL_TTF_REQUESTED_ && sdl_ttf_init_success_ )
        {
            TTF_Quit();
        }

        if( SDL_IMAGE_REQUESTED_ && sdl_image_init_success_ )
        {
            IMG_Quit();
        }

        hlp::delete_val( renderer_ );

        hlp::delete_val( window_ );

        if( sdl_init_success_ )
        {
            SDL_Quit();
        }
    }
}



/// <summary>
/// Get the window.
/// </summary>
/// <returns></returns>
SDL_Window* Initializer::win( void )
{
    return window_;
}



/// <summary>
/// Get the renderer.
/// </summary>
/// <returns>The renderer.</returns>
SDL_Renderer* Initializer::renderer( void )
{
    return renderer_;
}



bool Initializer::good( void )
{
    return
        created_ &&
        static_cast<bool>( window_ ) &&
        static_cast<bool>( renderer_ ) &&
        sdl_init_success_ &&
        ( sdl_image_init_success_ == SDL_IMAGE_REQUESTED_ ) &&
        ( sdl_ttf_init_success_ == SDL_TTF_REQUESTED_ );
}

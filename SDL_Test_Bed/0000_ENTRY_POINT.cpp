


#include<SDL.h>
#include<iostream>

#include "initializer.h"
#include "helper_funcs.h"
#include "input_handler.h"



constexpr bool INIT_SDL_image{ true };
constexpr bool INIT_SDL_TTF{ false };


constexpr const Uint32 FPS{ 240 };

constexpr const Uint32 MILLISECONDS_PER_SECOND{ 1000 };
constexpr const double TICKS_PER_FRAME{ static_cast<double>( MILLISECONDS_PER_SECOND ) / static_cast<double>( FPS ) };



bool frame_begin( SDL_Renderer* renderer, Uint32& begin_time, Input_Handler& IH );
void under_development( SDL_Window* window, SDL_Renderer* renderer, Input_Handler& IH );
void frame_end( SDL_Renderer* renderer, const Uint32& begin_time );



/// <summary>
/// Entry point
/// </summary>
/// <param name="argc">Command line argument Count.</param>
/// <param name="argv">Command lien argument Value(s).</param>
/// <returns>Exit status.</returns>
int SDL_main( int argc, char* argv[] )
{
    Initializer init( INIT_SDL_image, INIT_SDL_TTF );// , {} );

    if( !init.good() )
    {
        return -1;
    }


    Input_Handler input{};
    input.init();
    for( Uint32 begin_time{ 0 };
         frame_begin( init.renderer(), begin_time, input );
         frame_end( init.renderer(), begin_time ) )
    {
        under_development( init.win() ,init.renderer(), input );
    }

    return 0;
}




/// <summary>
/// Calls, objects, or other items being tested should be called from here.
/// </summary>
void under_development( SDL_Window* window, SDL_Renderer* renderer, Input_Handler& IH )
{
    //Things to be tested/tried go here.




    //
    return;
}






/// <summary>
/// Called at the beginning of every frame.  Begins time the frame duration,
/// polls SDL's event handler, and clears the window to be rendered to.
/// </summary>
/// <param name="renderer">The render for the window.</param>
/// <param name="begin_time">A reference to the timing variable.</param>
/// <param name="IH">A reference to the input handler object.</param>
/// <returns>false if the program should quit.</returns>
bool frame_begin( SDL_Renderer* renderer, Uint32& begin_time, Input_Handler& IH )
{
    begin_time = SDL_GetTicks();

    if( IH.poll() )
    {
        return false;
    }

    SDL_SetRenderDrawColor( renderer, 5, 85, 5, 0 );
    SDL_RenderClear( renderer );


    return true;
}



/// <summary>
/// Called at the end of every frame.  Calculates the frame delay
/// </summary>
/// <param name="renderer">The renderer for the window.</param>
/// <param name="begin_time">A reference to the timing variable.</param>
void frame_end( SDL_Renderer* renderer, const Uint32& begin_time )
{
    SDL_RenderPresent( renderer );

    auto frame_time = (SDL_GetTicks() - begin_time);
    if( frame_time < TICKS_PER_FRAME )
    {
        SDL_Delay( static_cast<Uint32>( TICKS_PER_FRAME - static_cast<double>( frame_time ) ) );
    }
    else
    {
        std::cerr << "ft+\n";
    }
}

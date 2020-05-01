#include<iostream>
#include "helper_funcs.h"
#include "input_handler.h"



std::array<Uint32, SCANCODE_QTY> Input_Handler::pressed_keys_;
std::bitset<SCANCODE_QTY> Input_Handler::just_released_keys_;
SDL_Event* Input_Handler::e_{nullptr};



bool Input_Handler::valid_key( const SDL_Scancode& scancode )
{
    auto valid = scancode < SCANCODE_QTY;
    if( !valid )
    {
        std::cerr << "\tError: Invalid scan code.  (" << scancode << ")\n";
    }
    return valid;
}



bool Input_Handler::poll( void )
{
    just_released_keys_.set( false );

    while( SDL_PollEvent( e_ ) )
    {
        switch( e_->type )
        {
        case SDL_QUIT:
            return true;  // Stop running.
        case SDL_KEYDOWN:
            ++pressed_keys_[ e_->key.keysym.scancode ];
            continue;
        case SDL_KEYUP:
            pressed_keys_[ e_->key.keysym.scancode ] = 0;
            just_released_keys_[ e_->key.keysym.scancode ] = true;
            continue;
        default:
            ;
        }
    }
    return false;  // Keep running.
}



Uint32 Input_Handler::key_down( SDL_Scancode scancode )
{
    if( valid_key( scancode ) )
    {
        return pressed_keys_[ scancode ];
    }
    return 0;
}



bool Input_Handler::key_released( SDL_Scancode scancode )
{
    return valid_key( scancode ) && just_released_keys_[ scancode ];
}



void Input_Handler::init( void )
{
    e_ = new SDL_Event;
    for( auto& pk : pressed_keys_ )
    {
        pk = 0;
    }
}

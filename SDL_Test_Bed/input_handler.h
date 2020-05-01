#pragma once



#include<SDL.h>
#include<array>
#include<bitset>



constexpr int SCANCODE_QTY{ 0x11d };



class Input_Handler
{
    static std::array<Uint32, SCANCODE_QTY> pressed_keys_;
    static std::bitset<SCANCODE_QTY> just_released_keys_;

    static SDL_Event* e_;

    bool valid_key( const SDL_Scancode& scancode );

public:

    bool poll( void );

    Uint32 key_down( SDL_Scancode scancode );
    bool key_released( SDL_Scancode scancode );

    void init( void );
};

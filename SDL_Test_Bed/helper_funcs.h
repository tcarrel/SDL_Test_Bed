#pragma once



#include<SDL.h>
#include<type_traits>



namespace hlp
{
    /// <summary>
    /// Deallocates an array and zeroes the pointer.  nullptr can be passed in
    /// safely.
    /// </summary>
    /// <param name="arr">The array to be deallocated.</param>
    /// <returns>true on success.</returns>
    template<typename T> void delete_array( T*& arr )
    {
        if( arr )
        {
            delete[] arr;
            arr = nullptr;
        }
    }



    /// <summary>
    /// Deallocates non-arrays and zeroes the pointer.  nullptr can be passed in safely.
    /// </summary>
    /// <param name="addr">The pointer to deallocate.</param>
    /// <returns>true on success.</returns>
    template<typename T> void delete_val( T*& addr )
    {
        if( addr )
        {
            if constexpr( std::is_same<T, SDL_Window>::value )
            {
                SDL_DestroyWindow( addr );
            }
            else if constexpr( std::is_same<T, SDL_Renderer>::value )
            {
                SDL_DestroyRenderer( addr );
            }
            else if constexpr( std::is_same<T, SDL_Texture>::value )
            {
                SDL_DestroyTexture( addr );
            }
            else if constexpr( std::is_same<T, SDL_Surface>::value )
            {
                SDL_FreeSurface( addr );
            }
            else if constexpr( std::is_same<T, SDL_cond>::value )
            {
                SDL_DestroyCond( addr );
            }
            else if constexpr( std::is_same<T, SDL_mutex>::value )
            {
                SDL_DestroyMutex( addr );
            }
            else if constexpr( std::is_same<T, SDL_sem>::value )
            {
                SDL_DestroySemaphore( addr );
            }
            else if constexpr( std::is_same<T, SDL_Cursor>::value )
            {
                SDL_FreeCursor( addr );
            }
            else if constexpr( std::is_same<T, SDL_PixelFormat>::value )
            {
                SDL_FreeFormat( addr );
            }
            else if constexpr( std::is_same<T, SDL_Palette>::value )
            {
                SDL_FreePalette( addr );
            }
            else if constexpr( std::is_same<T, SDL_RWops>::value )
            {
                SDL_FreeRW( addr );
            }
            else if constexpr( std::is_array<T>::value )
            {
                delete[] addr;
            }
            else
            {
                delete addr;
            }
            addr = nullptr;
        }
    }
}
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>


int main(void)
{

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("SDL Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Przykladowe okno",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       100, 100, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }


    SDL_Delay(5000);
    

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


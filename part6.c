#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (300)
#define WINDOW_HEIGHT (300)

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
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }


    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    
    SDL_Surface* surface = IMG_Load("resources/hello.bmp");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    
    SDL_Rect rect;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    float x_pos;
    float y_pos;
    
    int close_requested = 0;

    int stop = 0;
    
    while (!close_requested){
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = 1;
            }
        }
        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
        
        if(stop){
            x_pos=mouse_x-rect.w/2;
            y_pos=mouse_y-rect.h/2;
        }
        if ( buttons & SDL_BUTTON(SDL_BUTTON_LEFT) ){
            stop= !stop;
        }
        rect.y = (int) y_pos;
        rect.x = (int) x_pos;
        
        SDL_RenderClear(rend);


        SDL_RenderCopy(rend, tex, NULL, &rect);
        SDL_RenderPresent(rend);


        SDL_Delay(1000/60);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

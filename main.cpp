#include <SDL2/SDL.h>
#include <random>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    random_device rnd;
    mt19937 numbers(rnd());
    uniform_int_distribution<mt19937::result_type> red(1, 255);
    uniform_int_distribution<mt19937::result_type> green(1, 255);
    uniform_int_distribution<mt19937::result_type> blue(1, 255);

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Event event;
    SDL_Renderer* renderer;
    bool quit = false;

    // Tais erros de inicialização...
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        cout << "Erro ao iniciar o SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // Tratando a criação da janela
    window = SDL_CreateWindow("Joguin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Loop
    while (!quit)
    {   
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, red(rnd), green(rnd), blue(rnd), 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // Encerrando
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
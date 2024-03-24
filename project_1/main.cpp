#include <iostream>
#include <SDL2/SDL.h>
#include <unordered_set>
#include <unistd.h>

using namespace std;
const int WIDTH = 600, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event windowEvent;
    SDL_Rect rect = {20, 20, 100, 100};
    const int step = 1;
    string movement;
    const int fps = 60;

    SDL_Init(SDL_INIT_VIDEO);
    bool running = true;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (NULL == window)
    {
        cout << "Could not create window: " << SDL_GetError() << endl;
        return 1;
    }

    unordered_set<SDL_Keycode> keysPressed;

    while (running)
    {
        if (SDL_PollEvent(&windowEvent) or movement != "")
        {
            if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE))
            {
                running = false;
            }
            else if (windowEvent.type == SDL_KEYDOWN)
            {
                keysPressed.insert(windowEvent.key.keysym.sym);
            }
            else if (windowEvent.type == SDL_KEYUP)
            {
                keysPressed.erase(windowEvent.key.keysym.sym);
            }

            if (keysPressed.count(SDLK_SPACE))
            {
                movement = "";
            }
            else
            {
                if (keysPressed.count(SDLK_LEFT) or movement == "Left")
                {
                    rect.x -= step;
                    movement = "Left";
                }

                if (keysPressed.count(SDLK_RIGHT) or movement == "Right")
                {
                    rect.x += step;
                    movement = "Right";
                }

                if (keysPressed.count(SDLK_UP) or movement == "Up")
                {
                    rect.y -= step;
                    movement = "Up";
                }

                if (keysPressed.count(SDLK_DOWN) or movement == "Down")
                {
                    rect.y += step;
                    movement = "Down";
                }

                cout << "Position: " << rect.x << ", " << rect.y << endl;
            }
        }

        SDL_SetRenderDrawColor(renderer, 18, 40, 51, 1);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 144, 158, 159, 1);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        sleep(1 / fps);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
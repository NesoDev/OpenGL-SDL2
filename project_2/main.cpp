#include <iostream>
#include <SDL2/SDL.h>

const float WIDTH = 600.0f, HEIGHT = 600.0f;

class Object {
private:
    float position[2]; // X (x, y) = (x, y)
    float velocity[2]; // v (i, j) = vi + vj
    float range_x[2];
    int radius;
    int color[4]; // color = {r, g, b, a}
public:
    Object(float x, float y, float v_x, float v_y, int r, int* c) {
        position[0] = x;
        position[1] = y;

        velocity[0] = v_x;
        velocity[1] = v_y;

        range_x[0] = x - r;
        range_x[1] = x + r;

        radius = r;

        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        color[3] = c[3];
    };

    void draw(SDL_Renderer *renderer) {
        int rectX = static_cast<int>(position[0] - radius);
        int rectY = static_cast<int>(position[1] - radius);
        int rectW = static_cast<int>(radius * 2);
        int rectH = static_cast<int>(radius * 2);

        SDL_Rect rect = { rectX, rectY, rectW, rectH };
        SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
        SDL_RenderFillRect(renderer, &rect);
    };
};

int main( int argc, char *argv[] ) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    SDL_Init( SDL_INIT_VIDEO );
    bool running = true;
    SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

    SDL_GetRenderDrawColor( renderer, 0, 0, 0, 0 );

    if ( window == NULL ) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    while (running) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }

        int color[4] = {255, 255, 255, 255};
        Object o_1(WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f, 0.0f, 20, color);
        o_1.draw(renderer);

        SDL_RenderPresent(renderer);
    }
    return 0;
}

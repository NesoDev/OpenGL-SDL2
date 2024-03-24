#include <iostream>
#include <SDL2/SDL.h>

const float WIDTH = 600.0f, HEIGHT = 600.0f;
const 

class Particle {
private:
    float position[2]; 
    float velocity[2];
    float range_x[2];
    int radius;
    int* color;
    bool needsRedraw = true;
public:
    Particle(int x, int y, float v_x, float v_y, int r, int* c) : needsRedraw(true) {
        position[0] = x;
        position[1] = y;
        velocity[0] = v_x;
        velocity[1] = v_y;
        range_x[0] = x - r;
        range_x[1] = x + r;
        radius = r;
        color = new int[4];
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        color[3] = c[3];
    };

    ~Particle() {
        delete[] color;
    }

    void setNeedsRedraw(bool redraw) {
        needsRedraw = redraw;
    }

    void setPosition(float x, float y) {
        position[0] = x;
        position[1] = y;

        needsRedraw = true;
    }

    void draw(SDL_Renderer *renderer) {
        if (needsRedraw) {
            std::cout << "Particle drawed" << std::endl;
            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
            int x_int = static_cast<int>(position[0]);
            int y_int = static_cast<int>(position[1]);
            int x = 0;
            int y = radius;
            int d = 3 - 2 * radius;

            while (x <= y) {
                SDL_RenderDrawPoint(renderer, x_int + x, y_int + y);
                SDL_RenderDrawPoint(renderer, x_int - x, y_int + y);
                SDL_RenderDrawPoint(renderer, x_int + x, y_int - y);
                SDL_RenderDrawPoint(renderer, x_int - x, y_int - y);
                SDL_RenderDrawPoint(renderer, x_int + y, y_int + x);
                SDL_RenderDrawPoint(renderer, x_int - y, y_int + x);
                SDL_RenderDrawPoint(renderer, x_int + y, y_int - x);
                SDL_RenderDrawPoint(renderer, x_int - y, y_int - x);

                if (d < 0) {
                    d += 4 * x + 6;
                } else {
                    d += 4 * (x - y) + 10;
                    y--;
                }
                x++;
            }

            needsRedraw = false;
        }
    }
};

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event event;

    int num_particles = 20;
    Particle **particles = new Particle* [num_particles];

    SDL_Init(SDL_INIT_VIDEO);
    bool running = true;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);

    SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    Particle p_1(WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f, 0.0f, 1, new int[4]{184, 253, 113, 1});
    Particle p_2(WIDTH / 4.0f, HEIGHT / 4.0f, 0.0f, 0.0f, 180, new int[4]{184, 253, 113, 1});

    while (running) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                p_1.setPosition(event.window.data1 / 2.0f, event.window.data2 / 2.0f);
                p_2.setPosition(event.window.data1 / 4.0f, event.window.data2 / 4.0f);
                std::cout << "Ventana Redimensionada" << std::endl;
            }
        }

        p_1.draw(renderer);
        p_2.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

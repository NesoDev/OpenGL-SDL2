#include <iostream>
#include <SDL2/SDL.h>
#include <unordered_set>

using namespace std;
const int WIDTH = 600, HEIGHT = 600; // Definición de constantes para el ancho y alto de la ventana

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;     // Puntero a la ventana SDL
    SDL_Renderer *renderer = nullptr; // Puntero al renderizador SDL
    SDL_Event windowEvent;            // Estructura para manejar eventos de la ventana
    SDL_Rect rect = {20, 20, 100, 100};
    const int step = 2;

    SDL_Init(SDL_INIT_VIDEO); // Inicialización del subsistema de vídeo de SDL2
    bool running = true;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer); // Creación de la ventana y el renderizador

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Establecer el color de dibujo del renderizador a negro
    SDL_RenderClear(renderer);                      // Limpiar el renderizador con el color establecido

    if (NULL == window) {
        cout << "Could not create window: " << SDL_GetError() << endl; // Imprimir un mensaje de error si la ventana no se creó correctamente
        return 1;                                                      // Salir del programa con código de error
    }

    unordered_set<SDL_Keycode> keysPressed;

    while (running) {
        // Verificar si hay eventos en la cola de eventos de la ventana
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            } else if (windowEvent.type == SDL_KEYDOWN) {
                keysPressed.insert(windowEvent.key.keysym.sym);
            } else if (windowEvent.type == SDL_KEYUP) {
                keysPressed.erase(windowEvent.key.keysym.sym);
            }
            
            if (keysPressed.count(SDLK_LEFT)) {
                rect.x -= step;
            } else if (keysPressed.count(SDLK_RIGHT)) {
                rect.x += step;
            }

            if (keysPressed.count(SDLK_UP)) {
                rect.y -= step;
            } else if (keysPressed.count(SDLK_DOWN)) {
                rect.y += step;
            }
        }

        SDL_SetRenderDrawColor(renderer, 18, 40, 51, 1); // Establecer el color de dibujo del renderizador a negro
        SDL_RenderClear(renderer);                      // Limpiar el renderizador con el color establecido

        SDL_SetRenderDrawColor(renderer, 144, 158, 159, 1); // Establecer el color de dibujo del renderizador a blanco
        SDL_RenderFillRect(renderer, &rect);              // Dibujar un rectángulo utilizando la estructura rect definida anteriormente

        SDL_RenderPresent(renderer); // Mostrar los cambios realizados en el renderizador en la ventana
    }

    SDL_DestroyRenderer(renderer); // Liberar memoria utilizada por el renderizador
    SDL_DestroyWindow(window);     // Liberar memoria utilizada por la ventana
    SDL_Quit();                    // Cerrar SDL2 y liberar recursos utilizados por la biblioteca

    return EXIT_SUCCESS; // Salir del programa con código de éxito
}
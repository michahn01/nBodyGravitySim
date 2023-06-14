#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "utility/TextureHandler.h"
#include "utility/InputHandler.h"
#include "utility/MassConfigurer.h"
#include "utility/QuadTree.h"
#include "ProgramObjects/buttons/ExampleConfigsButton.h"
#include "ProgramObjects/Mass.h"
#include "ProgramObjects/buttons/StateChanger.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

enum simulation_states {
    CONFIG = 0,
    RUNNING = 1,
    PAUSED = 2
};

class Utilities {
public:
    Utilities(SDL_Renderer* renderer,
              TextureHandler* texture_handler,
              InputHandler* input_handler,
              MassConfigurer* mass_configurer,
              SDL_Window* window,
              std::vector<Button*>& config_buttons,
              std::vector<Button*>& run_buttons,
              std::vector<Button*>& pause_buttons,
              std::vector<Mass*>& masses,
              int &state, Uint32& curr_time, Uint32& prev_time) : 
              renderer(renderer), texture_handler(texture_handler), input_handler(input_handler),
              mass_configurer(mass_configurer), window(window), config_buttons(config_buttons),
              masses(masses), state(state), run_buttons(run_buttons), pause_buttons(pause_buttons),
              curr_time(curr_time), prev_time(prev_time) {}
    SDL_Renderer* renderer;
    TextureHandler* texture_handler;
    InputHandler* input_handler;
    MassConfigurer* mass_configurer;
    SDL_Window* window;
    std::vector<Button*>& config_buttons;
    std::vector<Button*>& run_buttons;
    std::vector<Button*>& pause_buttons;
    std::vector<Mass*>& masses;
    int &state;
    bool is_running = false;
    Uint32& curr_time;
    Uint32& prev_time;
};

void update(Utilities* util) {
    switch (util->state) {
        case CONFIG:
            {
            std::vector<Button*>& config_buttons = util->config_buttons;
            for (int i = 0; i < config_buttons.size(); ++i) {
                config_buttons[i]->update();
            }
            util->prev_time = SDL_GetTicks();
            break;
            }
        case RUNNING:
            {
            std::vector<Button*>& run_buttons = util->run_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < run_buttons.size(); ++i) {
                run_buttons[i]->update();
            }
            QuadTree quad_tree(masses);

            util->curr_time = SDL_GetTicks();
            int j = (util->curr_time - util->prev_time) / 5;
            util->prev_time = util->curr_time;
            for (int i = 0; i < j; ++i) {
                for (int i = 0; i < masses.size(); ++i) {
                    masses[i]->leapFrog1(5);
                }
                quad_tree.update();
                for (int i = 0; i < masses.size(); ++i) {
                    masses[i]->leapFrog2(5);
                }
            }

            break;
            }
        case PAUSED:
            {
            std::vector<Button*>& pause_buttons = util->pause_buttons;
            for (int i = 0; i < pause_buttons.size(); ++i) {
                pause_buttons[i]->update();
            }
            util->prev_time = SDL_GetTicks();
            break;
            }
    }
}

void handleEvents(Utilities* util) {
    util->input_handler->update(util->is_running);
    TextureHandler* texture_handler = util->texture_handler;
    InputHandler* input_handler = util->input_handler;
    texture_handler->shiftLeft(input_handler->isKeyDown(SDL_SCANCODE_LEFT));
    texture_handler->shiftRight(input_handler->isKeyDown(SDL_SCANCODE_RIGHT));
    texture_handler->shiftDown(input_handler->isKeyDown(SDL_SCANCODE_DOWN));
    texture_handler->shiftUp(input_handler->isKeyDown(SDL_SCANCODE_UP));
    if (!input_handler->isKeyDown(SDL_SCANCODE_Z)) return;
    Vector2D mouse_pos = input_handler->getMousePosition();
    if (!input_handler->isKeyDown(SDL_SCANCODE_LSHIFT)) {
        texture_handler->zoomIn(mouse_pos.getX(), mouse_pos.getY());
        return;
    }
    texture_handler->zoomOut(mouse_pos.getX(), mouse_pos.getY());
}

void render(Utilities* util) {
    SDL_RenderClear(util->renderer);
    switch (util->state) {
        case CONFIG:
            {
            std::vector<Button*>& config_buttons = util->config_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < config_buttons.size(); ++i) {
                config_buttons[i]->draw();
            }
            for (int i = 0; i < masses.size(); ++i) {
                masses[i]->draw();
            }
            break;
            }
        case RUNNING:
            {
            std::vector<Button*>& run_buttons = util->run_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < run_buttons.size(); ++i) {
                run_buttons[i]->draw();
            }
            for (int i = 0; i < masses.size(); ++i) {
                masses[i]->draw();
            }
            break;
            }
        case PAUSED:
            {
            std::vector<Button*>& pause_buttons = util->pause_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < pause_buttons.size(); ++i) {
                pause_buttons[i]->draw();
            }
            for (int i = 0; i < masses.size(); ++i) {
                masses[i]->draw();
            }
            }
    }
    SDL_RenderPresent(util->renderer);
}

bool loadAllTextures(Utilities* util) {
    if (!util->texture_handler->load("resources/textures/example_configs_buttons.png", "example_configs_buttons", util->renderer)) {
        return false;
    }
    if (!util->texture_handler->load("resources/textures/unstable_3_body.png", "unstable_3_body", util->renderer)) {
        return false;
    }
    if (!util->texture_handler->load("resources/textures/euler_3_body.png", "euler_3_body", util->renderer)) {
        return false;
    }
    if (!util->texture_handler->load("resources/textures/white_mass.png", "white_mass", util->renderer)) {
        return false;
    }        
    if (!util->texture_handler->load("resources/textures/start_simulation_button.png", "start_simulation_button", util->renderer)) {
        return false;
    }    
    if (!util->texture_handler->load("resources/textures/reset_button.png", "reset_button", util->renderer)) {
        return false;
    }        
    if (!util->texture_handler->load("resources/textures/pause_button.png", "pause_button", util->renderer)) {
        return false;
    }     
    if (!util->texture_handler->load("resources/textures/resume_button.png", "resume_button", util->renderer)) {
        return false;
    }            
    return true;
}

void mainloop (void *arg) {
    Utilities* util = static_cast<Utilities*>(arg);
    handleEvents(util);
    update(util);
    render(util);
}


int main() {
    SDL_Window* window = SDL_CreateWindow("test", 0, 0, 900, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer;
    if (window != 0) {
        std::cout << "window creation success\n";
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer != 0) {
            std::cout << "renderer creation success\n";
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        else {
            std::cout << "renderer init fail\n";
            return false; // renderer init fail
        }
    }
    else {
        std::cout << "window init fail\n";
        return false; // window init fail
    }
    TextureHandler th; 
    int state = CONFIG;
    InputHandler ih(state);
    std::vector<Button*> config_buttons;
    std::vector<Button*> run_buttons;
    std::vector<Button*> pause_buttons;
    std::vector<Mass*> masses;
    MassConfigurer mc(masses, renderer, &th, &ih); 
    Uint32 curr_time = 0; Uint32 prev_time = 0;
    Utilities util(renderer, &th, &ih, &mc, window, config_buttons, run_buttons, pause_buttons, masses, state, curr_time, prev_time);


    Mass::set_utilities(util.renderer, util.texture_handler, util.input_handler);
    Button::set_utilities(util.renderer, util.texture_handler, util.input_handler, util.mass_configurer);

    if (!loadAllTextures(&util)) return false;
    config_buttons.push_back(new StateChanger(200, 0, 200, 50, "start_simulation_button", 1));
    config_buttons.push_back(new ExampleConfigsButton(0, 0, 200, 50, "example_configs_buttons"));
    run_buttons.push_back(new StateChanger(0, 0, 67, 50, "pause_button", 2));
    run_buttons.push_back(new StateChanger(67, 0, 67, 50, "reset_button", 0));
    pause_buttons.push_back(new StateChanger(67, 0, 67, 50, "reset_button", 0));
    pause_buttons.push_back(new StateChanger(0, 0, 67, 50, "resume_button", 1));

    // following error is harmless
    emscripten_set_main_loop_arg(mainloop, &util, -1, 1);

}
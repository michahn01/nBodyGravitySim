#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "utility/TextureHandler.h"
#include "utility/InputHandler.h"
#include "utility/MassConfigurer.h"
#include "utility/ForceComputer.h"
#include "ProgramObjects/buttons/DropDownButton.h"
#include "ProgramObjects/Mass.h"
#include "ProgramObjects/buttons/StateChanger.h"
#include "ProgramObjects/MassPlacer.h"
#include "ProgramObjects/buttons/MassPlaceDropDown.h"

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
              std::vector<Object*>& config_buttons,
              std::vector<Object*>& run_buttons,
              std::vector<Object*>& pause_buttons,
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
    std::vector<Object*>& config_buttons;
    std::vector<Object*>& run_buttons;
    std::vector<Object*>& pause_buttons;
    std::vector<Mass*>& masses;
    int &state;
    bool is_running = false;
    Uint32& curr_time;
    Uint32& prev_time;
    int root_width = 1200;
};

void update(Utilities* util) {
    switch (util->state) {
        case CONFIG:
            {
            std::vector<Object*>& config_buttons = util->config_buttons;
            for (int i = 0; i < config_buttons.size(); ++i) {
                config_buttons[i]->update();
            }
            util->prev_time = SDL_GetTicks();
            break;
            }
        case RUNNING:
            {
            std::vector<Object*>& run_buttons = util->run_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < run_buttons.size(); ++i) {
                run_buttons[i]->update();
            }
            util->curr_time = SDL_GetTicks();
            int j = (util->curr_time - util->prev_time) / 5;
            util->prev_time = util->curr_time;
            for (int i = 0; i < j; ++i) {
                ForceComputer force_computer(masses, util->root_width);
                for (int i = 0; i < masses.size(); ++i) {
                    if (masses[i]->getPos().getX() > util->root_width) {
                        util->root_width = masses[i]->getPos().getX() + 100;
                    }
                    if (masses[i]->getPos().getY() > util->root_width) {
                        util->root_width = masses[i]->getPos().getY() + 100;
                    }
                    masses[i]->leapFrog1(5);
                }
                force_computer.updateWithBarnesHut();
                for (int i = 0; i < masses.size(); ++i) {
                    masses[i]->leapFrog2(5);
                }
            }

            break;
            }
        case PAUSED:
            {
            std::vector<Object*>& pause_buttons = util->pause_buttons;
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
            std::vector<Object*>& config_buttons = util->config_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < masses.size(); ++i) {
                masses[i]->draw();
            }
            for (int i = 0; i < config_buttons.size(); ++i) {
                config_buttons[i]->draw();
            }
            break;
            }
        case RUNNING:
            {
            std::vector<Object*>& run_buttons = util->run_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < masses.size(); ++i) {
                masses[i]->draw();
            }
            for (int i = 0; i < run_buttons.size(); ++i) {
                run_buttons[i]->draw();
            }
            break;
            }
        case PAUSED:
            {
            std::vector<Object*>& pause_buttons = util->pause_buttons;
            std::vector<Mass*>& masses = util->masses;
            for (int i = 0; i < masses.size(); ++i) {
                masses[i]->draw();
            }
            for (int i = 0; i < pause_buttons.size(); ++i) {
                pause_buttons[i]->draw();
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
    if (!util->texture_handler->load("resources/textures/spawn_particles_buttons.png", "spawn_particles_buttons", util->renderer)) {
        return false;
    }       
    if (!util->texture_handler->load("resources/textures/mass_placer.png", "mass_placer_settings", util->renderer)) {
        return false;
    }    
    if (!util->texture_handler->load("resources/textures/mass_count_1.png", "mass_count_1", util->renderer)) {
        return false;
    }      
    if (!util->texture_handler->load("resources/textures/mass_count_10.png", "mass_count_10", util->renderer)) {
        return false;
    }     
    if (!util->texture_handler->load("resources/textures/weight_default.png", "weight_default", util->renderer)) {
        return false;
    }      
    if (!util->texture_handler->load("resources/textures/weight_light.png", "weight_light", util->renderer)) {
        return false;
    }      
    if (!util->texture_handler->load("resources/textures/weight_heavy.png", "weight_heavy", util->renderer)) {
        return false;
    }      
    if (!util->texture_handler->load("resources/textures/place_particles.png", "place_particles", util->renderer)) {
        return false;
    }    
    if (!util->texture_handler->load("resources/textures/green_mass.png", "green_mass", util->renderer)) {
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

void cleanAll(Utilities* util) {
    util->mass_configurer->clear_current_config();
    delete util->input_handler;
    delete util->texture_handler;
    delete util->mass_configurer;
    std::vector<Object*>& config_buttons = util->config_buttons;
    std::vector<Object*>& run_buttons = util->run_buttons;
    std::vector<Object*>& pause_buttons = util->pause_buttons;
    for (int i = 0; i < config_buttons.size(); ++i) {
        delete config_buttons[i];
        config_buttons[i] = nullptr;
    }
    for (int i = 0; i < run_buttons.size(); ++i) {
        delete run_buttons[i];
        config_buttons[i] = nullptr;
    }
    for (int i = 0; i < pause_buttons.size(); ++i) {
        delete pause_buttons[i];
        config_buttons[i] = nullptr;
    }
}


int main() {
    SDL_Window* window = SDL_CreateWindow("test", 0, 0, 1000, 800, SDL_WINDOW_RESIZABLE);
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
            return 1; // renderer init fail
        }
    }
    else {
        std::cout << "window init fail\n";
        return 1; // window init fail
    }

    TextureHandler th; 
    int state = CONFIG;
    InputHandler ih(state);
    std::vector<Object*> config_buttons;
    std::vector<Object*> run_buttons;
    std::vector<Object*> pause_buttons;
    std::vector<Mass*> masses;
    MassConfigurer mc(masses, renderer, &th, &ih); 
    Uint32 curr_time = 0; Uint32 prev_time = 0;
    Utilities util(renderer, &th, &ih, &mc, window, config_buttons, run_buttons, pause_buttons, masses, state, curr_time, prev_time);


    Mass::set_utilities(util.renderer, util.texture_handler, util.input_handler);
    Object::set_utilities(util.renderer, util.texture_handler, util.input_handler, util.mass_configurer);


    MassPlacer* mass_placer = new MassPlacer(); 
    config_buttons.push_back(mass_placer); run_buttons.push_back(mass_placer); pause_buttons.push_back(mass_placer);

    if (!loadAllTextures(&util)) return 1;
    config_buttons.push_back(new StateChanger(400, 0, 200, 50, "start_simulation_button", 1));


    DropDownButton* spawn_particles_button = 
    new DropDownButton(200, 0, 200, 50, "spawn_particles_buttons", mass_placer->spawn_particle_button_dropped);
    spawn_particles_button->addDropDown(new NoninteractiveDropDown(200, 50, 200, 140, "mass_placer_settings"));
    spawn_particles_button->addDropDown(new MassPlaceDropDown(230, 85, 60, 35, "mass_count_1", 1, mass_placer->num_particles, mass_placer));
    spawn_particles_button->addDropDown(new MassPlaceDropDown(310, 85, 60, 35, "mass_count_10", 10, mass_placer->num_particles, mass_placer));
    spawn_particles_button->addDropDown(new MassPlaceDropDown(201, 155, 66, 35, "weight_light", 0.3, mass_placer->mass, mass_placer));
    spawn_particles_button->addDropDown(new MassPlaceDropDown(267, 155, 66, 35, "weight_default", 1, mass_placer->mass, mass_placer));
    spawn_particles_button->addDropDown(new MassPlaceDropDown(333, 155, 66, 35, "weight_heavy", 10, mass_placer->mass, mass_placer));
    spawn_particles_button->addDropDown(new PlaceParticles(200, 195, 200, 35, "place_particles", mass_placer));
    config_buttons.push_back(spawn_particles_button); 
    run_buttons.push_back(spawn_particles_button); 
    pause_buttons.push_back(spawn_particles_button);

    DropDownButton* example_configs_button = new DropDownButton(0, 0, 200, 50, "example_configs_buttons", mass_placer->example_configs_button_dropped);
    example_configs_button->addConfigDropDown(new DropDown(0, 50, 200, 35, "euler_3_body"), "resources/mass_configurations/euler_3_body.csv");
    example_configs_button->addConfigDropDown(new DropDown(0, 85, 200, 35, "unstable_3_body"), "resources/mass_configurations/unstable_3_body.csv");
    config_buttons.push_back(example_configs_button);

    run_buttons.push_back(new StateChanger(0, 0, 100, 50, "pause_button", 2));
    run_buttons.push_back(new StateChanger(100, 0, 100, 50, "reset_button", 0));
    pause_buttons.push_back(new StateChanger(100, 0, 100, 50, "reset_button", 0));
    pause_buttons.push_back(new StateChanger(0, 0, 100, 50, "resume_button", 1));


    // following error is harmless
    emscripten_set_main_loop_arg(mainloop, &util, -1, 1);



}
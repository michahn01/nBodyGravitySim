#ifndef MassConfigurer_h
#define MassConfigurer_h

#include "../ProgramObjects/Mass.h"
#include "TextureHandler.h"
#include "InputHandler.h"
#include <unordered_map>
#include "csv.h"
#include <vector>

class MassConfigurer {
public:
    MassConfigurer(std::vector<Mass*>& m, SDL_Renderer* r, TextureHandler* t, InputHandler* i) : masses(m) {
        renderer = r; texture_handler = t; input_handler = i;
    }
    void load_configuration(std::string config_file) {
        clear_current_config();
        io::CSVReader<10> in(config_file);
        in.read_header(io::ignore_extra_column, "mass", "w", "h", "p_x", "p_y", "v_x", "v_y", "a_x", "a_y", "texture_ID");
        double mass; double w; double h; 
        double p_x; double p_y; 
        double v_x; double v_y;
        double a_x; double a_y;
        std::string texture_ID;
        while (in.read_row(mass, w, h, p_x, p_y, v_x, v_y, a_x, a_y, texture_ID)) {
            // std::cout << mass << " " << w << " " << h << " " << p_x << " " << p_y << " " << v_x << " " << v_y << " " << a_x << " " << a_y << " " << texture_ID << std::endl;
            masses.push_back(new Mass(mass, w, h,p_x, p_y, v_x, v_y, a_x, a_y, texture_ID)); 
            masses_size++;
        }
    };
    void add_mass(Mass* m) {
        masses.push_back(m);
        masses_size++;
    }
    void clear_current_config() {
        while (!masses.empty()) {
            delete masses.back();
            masses.pop_back();
        }
        masses_size = 0;
    }
    int masses_size = 0;

private:
    std::vector<Mass*>& masses;

    SDL_Renderer* renderer;
    TextureHandler* texture_handler;
    InputHandler* input_handler;
};


#endif
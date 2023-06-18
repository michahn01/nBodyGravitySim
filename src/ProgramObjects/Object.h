#ifndef Object_h
#define Object_h

#include "../utility/MassConfigurer.h"
#include <vector>
class Object {
protected:
    virtual void clickBehavior();
    enum display_state {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };
    static SDL_Renderer* renderer;
    static TextureHandler* texture_handler;
    static InputHandler* input_handler;
    static MassConfigurer* mass_configurer;
public:
    Object();
    Object(int x, int y, int w, int h, std::string ID);
    virtual void draw();
    virtual void update();
    virtual void clean();
    int current_row;
    int current_frame;
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    int width;
    int height;
    std::string texture_ID;
    
    static void set_utilities(SDL_Renderer* r, TextureHandler* t, InputHandler* i, MassConfigurer* m);
};


#endif
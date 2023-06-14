#ifndef Mass_h
#define Mass_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "../utility/TextureHandler.h"
#include "../utility/InputHandler.h"
#include "../utility/Vector2D.h"


class Mass {
public:
    virtual void draw();
    virtual void update(int dT);
    virtual void clean();
    Mass();
    Mass(float ms, float w, float h, 
         float p_x, float p_y, 
         float v_x, float v_y,
         float a_x, float a_y,
         std::string textureID) : 
         mass(ms), width(w), height(h), 
         pos(p_x, p_y), vel(v_x, v_y), acc(a_x, a_y),
         texture_ID(textureID) { }
    virtual ~Mass() {
    }
    static void set_utilities(SDL_Renderer* r, TextureHandler* t, InputHandler* i);
    static SDL_Renderer* renderer;
    static TextureHandler* texture_handler;
    static InputHandler* input_handler;
    Vector2D getPos() { return pos; }
    Vector2D getVel() { return vel; }
    Vector2D getAcc() { return acc; }
    Vector2D& getPosRef() { return pos; }
    Vector2D& getVelRef() { return vel; }
    Vector2D& getAccRef() { return acc; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getMass() { return mass; }
    void setWidth(float x) { width = x; }
    void setHeight(float x) { height = x; }
    void setMass(float x) { mass = x; }
    void setPos(Vector2D x) { pos = x; }
    void setVel(Vector2D x) { vel = x; }
    void setAcc(Vector2D x) { acc = x; }

    void leapFrog1(int dT);
    void leapFrog2(int dT);
protected:
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    float width;
    float height;
    std::string texture_ID;
    int current_frame = 0;
    float mass;
};

#endif
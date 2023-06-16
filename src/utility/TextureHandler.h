#ifndef TextureHandler_h
#define TextureHandler_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <iostream>


class TextureHandler {
public:
    bool load(std::string fileName, 
              std::string id, 
              SDL_Renderer* renderer);

    // draw
    void draw(std::string id, 
              int dest_x, int dest_y, 
              int dest_width, int dest_height, 
              int src_x, int src_y, 
              int src_width, int src_height,
              SDL_Renderer* renderer, 
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    // drawframe
    void drawFrame(std::string id, 
                   int dest_x, int dest_y, 
                   int dest_width, int dest_height, 
                   int src_x, int src_y, 
                   int src_width, int src_height,
                   int current_row, int current_frame,
                   SDL_Renderer* renderer, 
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    // draw with zoom
    void drawZoom(std::string id, 
              int dest_x, int dest_y, 
              int dest_width, int dest_height, 
              int src_x, int src_y, 
              int src_width, int src_height,
              SDL_Renderer* renderer, 
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    ~TextureHandler() {
        std::cout << "TextureHandler dtor run" << std::endl;
    }
    
    void clearFromTextureMap(std::string id);

    float getZoomFactor() { return zoom_factor; }
    int getXShift() { return x_shift; }
    int getYShift() { return y_shift; }

    void setZoomFactor(float zf) { zoom_factor = zf; }
    void setXShift(int x) { x_shift = x; }
    void setYShift(int y) { y_shift = y; }

    void zoomIn(int x, int y) { 
        curr = SDL_GetTicks();
        if (curr - previous_zoom_time < 200) return;
        zoom_factor *= 1.5;
        x_shift += (x + x_shift) * 0.5;
        y_shift -= (y - y_shift) * 0.5;
        previous_zoom_time = curr;
    }
    void zoomOut(int x, int y) { 
        curr = SDL_GetTicks();
        if (curr - previous_zoom_time < 200) return;
        zoom_factor /= 1.5;
        x_shift -= (x + x_shift) * 0.3333;
        y_shift += (y - y_shift) * 0.3333;
        previous_zoom_time = curr;
    }

    void shiftRight(int b) { x_shift += 2 * b; }
    void shiftLeft(int b) { x_shift -= 2 * b; }

    void shiftUp(int b) { y_shift += 2 * b; }
    void shiftDown(int b) { y_shift -= 2 * b; }

    void resetCamera() {
        zoom_factor = 1.0f;
        x_shift = -450;
        y_shift = 300;
    }


private:
    std::map<std::string, SDL_Texture*> textures_inventory;
    float zoom_factor = 1.0f;
    int x_shift = -450;
    int y_shift = 300;
    Uint32 previous_zoom_time = 0;
    Uint32 curr;
    

};

#endif


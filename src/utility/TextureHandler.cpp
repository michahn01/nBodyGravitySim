#include "TextureHandler.h"
#include <iostream>

bool TextureHandler::load(std::string fileName, std::string 
id, SDL_Renderer* renderer) {
    std::cout << "load attempt" << std::endl;
    SDL_Surface* temp_surface = IMG_Load(fileName.c_str());
    if (temp_surface == 0) {
        return false;
    }
    std::cout << "load successful" << std::endl;
    SDL_Texture* texture =
    SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    if (texture != 0) {
        textures_inventory[id] = texture;
        return true;
    }
    return false;
}


void TextureHandler::draw(std::string id, 
                          int dest_x, int dest_y, 
                          int dest_width, int dest_height, 
                          int src_x, int src_y, 
                          int src_width, int src_height,
                          SDL_Renderer* renderer, 
                          SDL_RendererFlip flip) {
    SDL_Rect dest_rect;
    dest_rect.w = dest_width;
    dest_rect.h = dest_height;
    dest_rect.x = dest_x;
    dest_rect.y = dest_y;

    SDL_Rect src_rect;
    src_rect.w = src_width;
    src_rect.h = src_height;
    src_rect.x = src_x;
    src_rect.y = src_y;

    SDL_RenderCopyEx(renderer, textures_inventory[id], &src_rect,
    &dest_rect, 0, 0, flip);
}

void TextureHandler::drawFrame(std::string id, 
                               int dest_x, int dest_y, 
                               int dest_width, int dest_height, 
                               int src_x, int src_y, 
                               int src_width, int src_height,
                               int current_row, int current_frame,
                               SDL_Renderer* renderer, 
                               SDL_RendererFlip flip) {

    SDL_Rect dest_rect;
    dest_rect.w = dest_width;
    dest_rect.h = dest_height;
    dest_rect.x = dest_x;
    dest_rect.y = dest_y;

    SDL_Rect src_rect;
    src_rect.w = src_width;
    src_rect.h = src_height;
    src_rect.x = src_x + src_width * current_frame;
    src_rect.y = src_y + src_height * current_row;
    // std::cout << src_rect.x << " " << src_rect.y << " " << current_frame << std::endl;

    SDL_RenderCopyEx(renderer, textures_inventory[id], &src_rect,
    &dest_rect, 0, 0, flip);
}

void TextureHandler::drawZoom(std::string id, 
                          int dest_x, int dest_y, 
                          int dest_width, int dest_height, 
                          int src_x, int src_y, 
                          int src_width, int src_height,
                          SDL_Renderer* renderer, 
                          SDL_RendererFlip flip) {
    SDL_Rect dest_rect;
    dest_rect.w = dest_width * zoom_factor;
    dest_rect.h = dest_height * zoom_factor;
    dest_rect.x = dest_x * zoom_factor - x_shift;
    dest_rect.y = dest_y * zoom_factor + y_shift;

    SDL_Rect src_rect;
    src_rect.w = src_width;
    src_rect.h = src_height;
    src_rect.x = src_x;
    src_rect.y = src_y;

    SDL_RenderCopyEx(renderer, textures_inventory[id], &src_rect,
    &dest_rect, 0, 0, flip);
}

void TextureHandler::clearFromTextureMap(std::string id)
{
 textures_inventory.erase(id);
}
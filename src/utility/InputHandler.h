#ifndef InputHandler_h
#define InputHandler_h

#include "SDL2/SDL.h"
#include "Vector2D.h"
#include <vector>
#include <unordered_map>


enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
public:
    InputHandler(int& state);
    ~InputHandler() {}
    void update(bool &is_running);
    void clean();
    bool getMouseButtonState(int buttonNumber);
    Vector2D getMousePosition();
    bool isKeyDown(SDL_Scancode key);
    void changeState(int s);
    int getState() { return state; };

    static InputHandler input_handler;
    
private:
    int x = 1; 
    std::vector<bool> m_mouseButtonStates = { false, false, false };
    Vector2D m_mousePosition;
    const Uint8* m_keystates;
    int& state;
};


#endif
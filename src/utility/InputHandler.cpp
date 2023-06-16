#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(int& s) : m_mousePosition(0, 0), state(s) {
}

void InputHandler::update(bool &is_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            is_running = false; break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    m_mouseButtonStates[LEFT] = true;
                case SDL_BUTTON_MIDDLE:
                    m_mouseButtonStates[MIDDLE] = true;
                case SDL_BUTTON_RIGHT:
                    m_mouseButtonStates[RIGHT] = true;
            }
            break;
        case SDL_MOUSEBUTTONUP: 
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    m_mouseButtonStates[LEFT] = false;
                case SDL_BUTTON_MIDDLE:
                    m_mouseButtonStates[MIDDLE] = false;
                case SDL_BUTTON_RIGHT:
                    m_mouseButtonStates[RIGHT] = false;
            }
            break;
        case SDL_MOUSEMOTION:
            m_mousePosition.setX(event.motion.x);
            m_mousePosition.setY(event.motion.y);
        }
        m_keystates = SDL_GetKeyboardState(0); 
    }
}

void InputHandler::clean() {

}

bool InputHandler::getMouseButtonState(int buttonNumber) {
    return m_mouseButtonStates[buttonNumber];
}

Vector2D InputHandler::getMousePosition() {
    return m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    return m_keystates != 0 && m_keystates[key] == 1;
}

void InputHandler::changeState(int s) {
    state = s;
}
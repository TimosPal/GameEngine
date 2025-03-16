#ifndef KEY_STATE_H
#define KEY_STATE_H

namespace Engine {

struct KeyState {
    enum class Type {
        Pressed = 0b0001,
        Hold = 0b0011,
        Released = 0b0100,
        NotPressed = 0b1000
    };

    Type type;

    KeyState() : type(Type::NotPressed) {}
};

} // Engine

#endif // !KEY_STATE_H

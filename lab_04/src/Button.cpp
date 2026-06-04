#include "Button.hpp"

Button::Button(int f, int d, QObject* parent) : QObject(parent), state(ButtonState::INACTIVE), floor(f), direction(d)
{
}

ButtonState Button::getState() const
{
    return state;
}

void Button::reset()
{
    state = ButtonState::INACTIVE;
}

void Button::onClicked()
{
    if (state == ButtonState::INACTIVE)
    {
        state = ButtonState::ACTIVE;
        emit callRequested(floor, direction);
    }
}
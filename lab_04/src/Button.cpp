#include "Button.hpp"


Button::Button(int floor, Direction direction, QWidget *parent) : _floor(floor), _direction(direction), _state(ButtonState::INACTIVE) 
{ 
    connect(this, &QPushButton::clicked, this, &Button::pressSlot);
    connect(this, &Button::unpressSignal, this, &Button::unpressSlot);
}


int Button::getFloor() const
{
    return _floor;
}


void Button::setFloor(const int newFloor) noexcept
{
    _floor = newFloor;
}     


void Button::setState(const ButtonState newState) noexcept
{
    _state = newState;
}


// =========================
//           Слоты
// =========================


void Button::pressSlot()
{
    if (_state != ButtonState::INACTIVE)
        return;
    
    _state = ButtonState::ACTIVE;

    emit pressSignal(_floor);
}


void Button::unpressSlot()
{
    if (_state != ButtonState::ACTIVE)
        return;

    _state = ButtonState::INACTIVE;
}
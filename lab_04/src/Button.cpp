#include "Button.hpp"


Button::Button(int floor, Direction direction, QWidget *parent = nullptr) : _floor(floor), _direction(direction), _state(ButtonState::INACTIVE) 
{ 
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(pressSlot()));
    QObject::connect(this, SIGNAL(unpressSignal()), this, SLOT(unpressSlot()));
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
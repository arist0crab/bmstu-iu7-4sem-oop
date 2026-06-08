#include "Doors.hpp"


Doors::Doors(QObject* parent) : _state(DoorsState::CLOSE), _timer(this) 
{ 
    _timer.setSingleShot(true);

    connect(&_timer, &QTimer::timeout, this, [this]() 
    {
        if (_state == DoorsState::OPENING)
            emit openedSignal();
        else if (_state == DoorsState::CLOSING)
            emit closedSignal();
    });

    connect(this, &Doors::openedSignal, this, &Doors::openSlot);
    connect(this, &Doors::closedSignal, this, &Doors::closeSlot);
}


DoorsState Doors::getState() const noexcept
{
    return _state;
}


// =========================
//           Слоты
// =========================


void Doors::startOpeningSlot()
{
    if (_state != DoorsState::CLOSE && _state != DoorsState::CLOSING)
        return;

    _state = DoorsState::OPENING;
    emit doorsStateChanged(_state);

    _timer.start(DOOR_TIME);
}


void Doors::openSlot()
{
    if (_state != DoorsState::OPENING)
        return;

    _state = DoorsState::OPEN;
    emit doorsStateChanged(_state);
}


void Doors::startClosingSlot()
{
    if (_state != DoorsState::OPEN)
        return;

    _state = DoorsState::CLOSING;
    emit doorsStateChanged(_state);

    _timer.start(DOOR_TIME);
}


void Doors::closeSlot()
{
    if (_state != DoorsState::CLOSING)
        return;

    _state = DoorsState::CLOSE;
    emit doorsStateChanged(_state);
}


#include "Cabin.hpp"


Cabin::Cabin(QObject* parent) : QObject(parent), _state(CabinState::IDLE), _moveTimer(this), _waitTimer(this)
{
    _moveTimer.setSingleShot(true);
    _waitTimer.setSingleShot(true);
    
    connect(&_moveTimer, &QTimer::timeout, this, &Cabin::onMoveTimeout);
    connect(&_waitTimer, &QTimer::timeout, this, &Cabin::onWaitTimeout);
    
    connect(&_doors, &Doors::doorsOpenedSignal, this, &Cabin::serveSlot);
    connect(&_doors, &Doors::doorsClosedSignal, this, &Cabin::idleSlot);
    
    connect(&_doors, &Doors::doorsStateChanged, this, &Cabin::doorsStateChanged);
}

CabinState Cabin::getState() const noexcept
{
    return _state;
}

// === обработчики таймеров ===

void Cabin::onMoveTimeout()
{
    emit cabinFloorReached();
}

void Cabin::onWaitTimeout()
{
    _doors.startClosingSlot(); 
}

// === слоты ===

void Cabin::moveSlot()
{
    if (_state == CabinState::SERVE) 
        return;
    
    _state = CabinState::MOVE;
    emit cabinStateChanged(_state);
    
    _moveTimer.start(MOVE_TIME);
}

void Cabin::serveSlot()
{
    if (_state == CabinState::SERVE)
    {
        emit cabinDoorsOpened();
        _waitTimer.start(WAIT_TIME);
        return;
    }

    if (_state != CabinState::SERVE)
    {
        _moveTimer.stop();
        _state = CabinState::SERVE;
        
        emit cabinFloorReached();
        emit cabinStateChanged(_state);
        
        _doors.startOpeningSlot();
    }
}


void Cabin::idleSlot()
{
    if (_state != CabinState::SERVE)
        return;
    
    _waitTimer.stop();
    emit cabinDoorsClosed();
    
    _state = CabinState::IDLE;
    emit cabinStateChanged(_state);
}
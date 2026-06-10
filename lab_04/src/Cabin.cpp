#include "Cabin.hpp"


Cabin::Cabin(QObject* parent) : QObject(parent), _state(CabinState::IDLE), _moveTimer(this), _waitTimer(this)
{
    _moveTimer.setSingleShot(true);
    _waitTimer.setSingleShot(true);
    
    connect(&_moveTimer, &QTimer::timeout, this, &Cabin::onMoveTimeout);
    connect(&_waitTimer, &QTimer::timeout, this, &Cabin::onWaitTimeout);
    
    // TODO на сигналы должны быть подписаны слоты
    connect(&_doors, &Doors::doorsOpenedSignal, this, &Cabin::onDoorsOpened);
    connect(&_doors, &Doors::doorsClosedSignal, this, &Cabin::onDoorsClosed);
    
    connect(&_doors, &Doors::doorsStateChanged, this, &Cabin::doorsStateChanged);
}

CabinState Cabin::getState() const noexcept
{
    return _state;
}

void Cabin::onDoorsOpened()
{
    if (_state == CabinState::WAIT)
    {
        _waitTimer.start(WAIT_TIME);
        emit doorsOpened();
    }
}

void Cabin::onDoorsClosed()
{
    if (_state == CabinState::WAIT)
    {
        freeSlot();
        emit doorsClosed();
    }
}

// === обработчики таймеров ===

void Cabin::onMoveTimeout()
{
    emit floorReached();
}

void Cabin::onWaitTimeout()
{
    _doors.startClosingSlot(); 
}

// === слоты ===

void Cabin::moveSlot()
{
    if (_state == CabinState::WAIT) 
        return;
    
    _state = CabinState::MOVE;
    emit cabinStateChanged(_state);
    
    _moveTimer.start(MOVE_TIME);
}

void Cabin::stopSlot()
{
    if (_state != CabinState::MOVE && _state != CabinState::IDLE)
        return;

    
    _moveTimer.stop();
    
    _state = CabinState::WAIT;
    emit cabinStateChanged(_state);
    
    _doors.startOpeningSlot();
}

void Cabin::freeSlot()
{
    if (_state != CabinState::WAIT)
        return;
    
    _waitTimer.stop();
    
    _state = CabinState::IDLE;
    emit cabinStateChanged(_state);
}
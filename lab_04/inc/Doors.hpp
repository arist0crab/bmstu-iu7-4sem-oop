#pragma once

#include "data.hpp"
#include <QObject>
#include <QTimer>


enum class DoorsState
{
    OPEN,
    CLOSE,
    OPENING,
    CLOSING
};


class Doors : public QObject
{
    Q_OBJECT 
    
    public:
        explicit Doors(QObject* parent = nullptr);
        ~Doors() override = default;

        DoorsState getState() const noexcept;

    signals:
        void openedSignal();
        void closedSignal();
        void doorsStateChanged(DoorsState state);

    public slots:
        void startOpeningSlot(); 
        void openSlot();
        void startClosingSlot();
        void closeSlot();

    private:
        DoorsState _state;
        QTimer _timer;
};
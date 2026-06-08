#pragma once


#include "data.hpp"
#include <QObject>
#include <QPushButton>


enum class ButtonState
{
    ACTIVE, 
    INACTIVE
};


class Button : public QPushButton
{
    Q_OBJECT

    public:
        explicit Button(int floor, Direction direction, QWidget *parent = nullptr);
        ~Button() override = default;

        int getFloor() const;
        void setFloor(const int newFloor) noexcept;
        void setState(const ButtonState newState) noexcept;
    
    signals:
        void pressSignal(int floor);
        void unpressSignal();

    public slots:
        void pressSlot();
        void unpressSlot();

    private:
        int _floor;
        ButtonState _state;
        Direction _direction;
};

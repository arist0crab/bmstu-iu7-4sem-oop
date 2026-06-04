#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QObject>

enum class ButtonState
{
    INACTIVE,
    ACTIVE
};

class Button : public QObject
{
    Q_OBJECT

    public:
        Button(int f, int d, QObject* parent = nullptr);
        ButtonState getState() const;
        void reset();

    signals:
        void callRequested(int f, int d);

    private slots:
        void onClicked();

    private:
        ButtonState state;
        int floor;
        int direction;
};

#endif
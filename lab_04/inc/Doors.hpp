#ifndef DOORS_HPP
#define DOORS_HPP

#include <QObject>
#include <QTimer>

enum class DoorState
{
    CLOSED,
    OPENING,
    OPEN,
    CLOSING
};

class Doors : public QObject
{
    Q_OBJECT

    public:
        Doors(QObject* parent = nullptr);
        DoorState getState() const;

    signals:
        void opened();
        void closed();
        void stateChanged(DoorState s);

    public slots:
        void onOpenRequest();
        void onCloseRequest();

    private slots:
        void onStateTimeout();

    private:
        DoorState state;
        QTimer* timer;
};

#endif
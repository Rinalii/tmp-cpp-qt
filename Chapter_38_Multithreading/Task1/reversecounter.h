#ifndef REVERSECOUNTER_H
#define REVERSECOUNTER_H

#include <QTimer>

class ReverseCounter : public QObject
{
    Q_OBJECT
public:
    ReverseCounter(QObject* parent = nullptr);
    ~ReverseCounter();

signals:
    void signalValueChanged(int value);
    void signalFinished();

public slots:
    void slotStartTimer();

private slots:
    void slotReduceCounter();

private:
    QTimer* timer_;
    int counter_;
};

#endif // REVERSECOUNTER_H

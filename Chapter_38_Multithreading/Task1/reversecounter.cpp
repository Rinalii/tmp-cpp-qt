#include "reversecounter.h"

ReverseCounter::ReverseCounter(QObject *parent)
    : QObject(parent) {
    counter_ = 10;
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &ReverseCounter::slotReduceCounter);
}

ReverseCounter::~ReverseCounter() {
    timer_->stop();
}

void ReverseCounter::slotReduceCounter() {
    --counter_;
    emit signalValueChanged(counter_);
    if(counter_ <= 0) {
        emit signalFinished();
        timer_->stop();
    }
}

void ReverseCounter::slotStartTimer() {
    counter_ = 10;
    emit signalValueChanged(counter_);
    if(!timer_->isActive()) {
        timer_->start();
    }
}

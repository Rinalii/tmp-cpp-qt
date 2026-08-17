#include "mainwindow.h"

#include <QObject>

#include <QLCDNumber>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include "reversecounter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QWidget* central = new QWidget(this);

    lcd_number_ = new QLCDNumber(this);
    start_btn_ = new QPushButton("Start", this);

    QVBoxLayout* v_layout = new QVBoxLayout(this);
    v_layout->addWidget(lcd_number_);
    v_layout->addWidget(start_btn_);

    central->setLayout(v_layout);
    setCentralWidget(central);

    thread_ = new QThread(this);
    reverse_counter_ = new ReverseCounter(this);

    reverse_counter_->moveToThread(thread_);

    connect(start_btn_, &QPushButton::clicked, this, [this](){
        if(!thread_->isRunning()) {
            thread_->start();
        }
        start_btn_->setEnabled(false);
    });

    connect(thread_, &QThread::started, reverse_counter_, &ReverseCounter::slotStartTimer);
    connect(thread_, &QThread::finished, this, [this]() {
        start_btn_->setEnabled(true);
    });
    connect(reverse_counter_, &ReverseCounter::signalValueChanged, lcd_number_, QOverload<int>::of(&QLCDNumber::display));
    connect(reverse_counter_, &ReverseCounter::signalFinished, thread_, &QThread::quit);
}

MainWindow::~MainWindow() {
    if (thread_->isRunning()) {
        thread_->quit();
        thread_->wait();
    }
}

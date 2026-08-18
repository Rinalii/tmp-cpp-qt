#include "mainwindow.h"

#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>

#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);

    progress_bar_ = new QProgressBar(this);
    text_edit_ = new QTextEdit(this);

    QVBoxLayout* v_layout = new QVBoxLayout(this);

    v_layout->addWidget(progress_bar_);
    v_layout->addWidget(text_edit_);

    central->setLayout(v_layout);
    setCentralWidget(central);

    QVector<QString> vec(100, "hellO");

    connect(&watcher_, &QFutureWatcherBase::finished, progress_bar_, &QProgressBar::reset);
    connect(&watcher_, &QFutureWatcherBase::progressRangeChanged, progress_bar_, &QProgressBar::setRange);
    connect(&watcher_, &QFutureWatcherBase::progressValueChanged, progress_bar_, &QProgressBar::setValue);

    connect(&watcher_, &QFutureWatcher<QString>::resultReadyAt, this,
            [this](int index) {
                QString result = watcher_.future().resultAt(index);
                text_edit_->append(result);
            });

    QFuture<QString> future = QtConcurrent::mapped(vec, [this](const QString& str) {
        return worker_.ConvertToUpper(str);
    });

    watcher_.setFuture(future);

}

MainWindow::~MainWindow() {
    if (watcher_.future().isRunning()) {
        watcher_.future().waitForFinished();
    }
}

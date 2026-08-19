#include "mainwindow.h"

#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>

#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);

    progress_bar_ = new QProgressBar(this);
    in_text_edit_ = new QTextEdit(this);
    in_text_edit_->setPlaceholderText("Введите строки, которые необходимо преобразовать к верхнему регистру");
    out_text_edit_ = new QTextEdit(this);
    out_text_edit_->setPlaceholderText("Результат обработки");
    out_text_edit_->setEnabled(false);

    QVBoxLayout* v_layout = new QVBoxLayout(this);

    v_layout->addWidget(progress_bar_);

    QHBoxLayout* h_layout = new QHBoxLayout(this);
    h_layout->addWidget(in_text_edit_);
    h_layout->addWidget(out_text_edit_);

    v_layout->addLayout(h_layout);

    start_btn_ = new QPushButton("Старт", this);
    v_layout->addWidget(start_btn_);

    central->setLayout(v_layout);
    setCentralWidget(central);

    connect(&watcher_, &QFutureWatcherBase::finished, progress_bar_, &QProgressBar::reset);
    connect(&watcher_, &QFutureWatcherBase::progressRangeChanged, progress_bar_, &QProgressBar::setRange);
    connect(&watcher_, &QFutureWatcherBase::progressValueChanged, progress_bar_, &QProgressBar::setValue);

    connect(&watcher_, &QFutureWatcher<QString>::resultReadyAt, this,
            [this](int index) {
                QString result = watcher_.future().resultAt(index);
                out_text_edit_->append(result);
            });

    connect(start_btn_, &QPushButton::clicked, this, &MainWindow::slotStartClicked);
    connect(&watcher_, &QFutureWatcherBase::finished, this, &MainWindow::slotProcessFinished);
    connect(this, &MainWindow::signalStartProcess, this, &MainWindow::slotStartProcess);
}

MainWindow::~MainWindow() {
    if (watcher_.future().isRunning()) {
        watcher_.future().waitForFinished();
    }
}

void MainWindow::slotStartProcess(const QStringList& vec) {
    if (watcher_.future().isRunning()) {
        return;
    }
    QFuture<QString> future = QtConcurrent::mapped(vec, [this](const QString& str) {
        return worker_.ConvertToUpper(str);
    });

    watcher_.setFuture(future);
}

void MainWindow::slotStartClicked() {
    QString all_text = in_text_edit_->toPlainText();

    QStringList lines = all_text.split('\n', Qt::SkipEmptyParts);
    if(!lines.isEmpty()) {
        start_btn_->setEnabled(false);
        in_text_edit_->setEnabled(false);
        emit signalStartProcess(lines);
    }
}

void MainWindow::slotProcessFinished() {
    start_btn_->setEnabled(true);
    in_text_edit_->setEnabled(true);
}

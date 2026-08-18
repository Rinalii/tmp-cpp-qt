#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "toupperworker.h"

#include <QFutureWatcher>

class QProgressBar;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QProgressBar* progress_bar_;
    QTextEdit* text_edit_;

    ToUpperWorker worker_;
    QFutureWatcher<QString> watcher_;

};
#endif // MAINWINDOW_H

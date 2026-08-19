#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "toupperworker.h"

#include <QFutureWatcher>

class QProgressBar;
class QTextEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalStartProcess(const QStringList& list);

private slots:
    void slotStartProcess(const QStringList& vec);
    void slotStartClicked();
    void slotProcessFinished();

private:
    QProgressBar* progress_bar_;
    QTextEdit* in_text_edit_;
    QTextEdit* out_text_edit_;
    QPushButton* start_btn_;

    ToUpperWorker worker_;
    QFutureWatcher<QString> watcher_;

};
#endif // MAINWINDOW_H

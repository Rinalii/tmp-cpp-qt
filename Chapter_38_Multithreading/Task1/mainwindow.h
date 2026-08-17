#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLCDNumber;
class QPushButton;
class QThread;
class ReverseCounter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QLCDNumber* lcd_number_;
    QPushButton* start_btn_;

    QThread* thread_;
    ReverseCounter* reverse_counter_;
};
#endif // MAINWINDOW_H

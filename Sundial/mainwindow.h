#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStartSim_clicked();

private:
    Ui::MainWindow *ui;
    //класс консольного интерфейса программы
    Interface *program;

    void setPlotSettings();

};

#endif // MAINWINDOW_H

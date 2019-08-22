#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dateandtime.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPlotSettings();

    program = new Interface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStartSim_clicked()
{
    //получаем из формы дату
    QStringList parsedDate = ui->lineEditDate->text().split('.');

    int day = parsedDate.first().toInt();
    int month = parsedDate.at(1).toInt();
    int year = parsedDate.last().toInt();

    Date date(day, month, year);
    //получаем из формы местоположение
    int latGrad = ui->lineEditLatGrad->text().toInt();
    int latSec = ui->lineEditLatSec->text().toInt();
    int longGrad = ui->lineEditLongGrad->text().toInt();
    int longSec = ui->lineEditLongSec->text().toInt();

    Location loc{longGrad, longSec, latGrad, latSec};

    //получаем результаты моделирования
    QVector<QVector<double>> shad = program->oneDayAnalysis(date, loc);
    //отображаем полученные результаты
    ui->plotShadow->graph(0)->setData(shad.first(), shad.last());
    ui->plotShadow->replot();


}

void MainWindow::setPlotSettings(){


    ui->plotShadow->xAxis->setLabel("Z, m");
    ui->plotShadow->yAxis->setLabel("X, m");

    ui->plotShadow->xAxis->setRange(-20, 20);
    ui->plotShadow->yAxis->setRange(-20, 20);

    ui->plotShadow->addGraph();
    ui->plotShadow->graph(0)->setPen(QColor(50, 50, 50, 255));
    ui->plotShadow->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plotShadow->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    ui->plotShadow->replot();

}

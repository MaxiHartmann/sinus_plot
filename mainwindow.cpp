#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);

    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
    qv_x_sin.clear();
    qv_y_sin.clear();
}

void MainWindow::plot()
{
    ui->customPlot->graph(0)->setData(qv_x, qv_y);
    ui->customPlot->graph(1)->setData(qv_x_sin, qv_y_sin);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void MainWindow::plotSinus()
{
    freq = ui->bx_fb->value();
    amp = ui->bx_amp->value();
    qv_x_sin.clear();
    qv_y_sin.clear();

    // QVector<double> qv_x_sin(628), qv_y_sin(628);
    for (int i=0; i<628; ++i)
    {
      // qv_x_sin[i] = i * 0.01;
      qv_x_sin.append(i*0.01);
      // qv_y_sin[i] = qSin(i * 0.01 * freq);
      qv_y_sin.append(amp * qSin(i * 0.01 * freq));
    }
    plot();
    ui->customPlot->graph(1)->rescaleAxes();
    ui->customPlot->replot();
    ui->customPlot->update();
}


void MainWindow::on_btn_add_clicked()
{
    addPoint(ui->bx_x->value(), ui->bx_y->value());
    plot();
}


void MainWindow::on_btn_clear_clicked()
{
    clearData();
    plot();
}


void MainWindow::on_pushButton_clicked()
{
    ui->customPlot->graph(0)->rescaleAxes();
    plot();
}


void MainWindow::on_btn_plotSinus_clicked()
{
    plotSinus();
}


void MainWindow::on_btn_clear_2_clicked()
{
    clearData();
    plot();
}

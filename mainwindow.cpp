#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fftw3.h>
#include <iostream>
#include <math.h>

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

    // https://www.qcustomplot.com/index.php/support/forum/1616
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->customPlot->axisRect()->setRangeZoomAxes(ui->customPlot->xAxis, NULL); //To block y axis zoom NULL axis as horizontal
    ui->customPlot->setSelectionRectMode(QCP::srmZoom);

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
    periods = ui->bx_periods->value();

    qv_x_sin.clear();
    qv_y_sin.clear();

    double PI = M_PI;
    int samples = 101 * int(periods);
    double t = 0;
    double omega = 2 * PI * freq;
    for (int i=0; i < samples; i++)
    {
        std::cout << i << std::endl;
        t = double(i) / samples * periods;
        qv_x_sin.append(t);
        qv_y_sin.append(amp * qSin(omega * t));
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

void MainWindow::on_bx_fb_valueChanged()
{
   plotSinus();
}

void MainWindow::on_bx_amp_valueChanged()
{
   plotSinus();
}

void MainWindow::on_btn_FFT_clicked()
{
    int n = 100;
    fftw_complex x[n];
    fftw_complex y[n];
    for (int i = 0; i < n; i++)
    {
        x[i][REAL] = i + 1; // 1, 2, 3, 4, 5
        x[i][IMAG] = 0;
    }
    fftw_plan plan = fftw_plan_dft_1d(n, x, y, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    // Do some cleaning
    fftw_destroy_plan(plan);
    fftw_cleanup();
    std::cout << "FFT" << std::endl;
    for (int i = 0; i < n; i++)
    {
        if (y[i][REAL] < 0){
            std::cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << std::endl;
        } else {
            std::cout << y[i][REAL] << " + " << y[i][IMAG] << "i" << std::endl;
        }
    }
}

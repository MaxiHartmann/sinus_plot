#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define REAL 0
#define IMAG 1

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPoint(double x, double y);
    void clearData();
    void plot();
    void plotSinus();


private slots:
    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_pushButton_clicked();

    void on_btn_plotSinus_clicked();

    void on_btn_clear_2_clicked();

    void on_bx_fb_valueChanged();

    void on_bx_amp_valueChanged();

    void on_btn_FFT_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;
    QVector<double> qv_x_sin, qv_y_sin;
    double freq, amp;
    double periods;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;
    // QVector<double> qv_x_sin, qv_y_sin;
};
#endif // MAINWINDOW_H

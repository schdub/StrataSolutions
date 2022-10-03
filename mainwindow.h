#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QThread>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QCPGraph;
class QCustomPlot;
class RandDataProducer;

class MainWindow : public QMainWindow {
    Q_OBJECT

    QThread thread_;
    QScopedPointer<Ui::MainWindow> ui_;
    QCPGraph * graph_;
    QScopedPointer<RandDataProducer> worker_;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setPlotData(QVector<double> x, QVector<double> y);

    void on_tbStart_pressed();
    void on_tbPause_pressed();
    void on_tbStop_pressed();
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QDebug>
#include <QVector>

#include "randdataproducer.h"

// ////////////////////////////////////////////////////////////////////////// //

const double DATA_PRODUCER_MIN = 0;
const double DATA_PRODUCER_MAX = 10;
const QColor COLOR_DEFAULT(0x5b, 0x9b, 0xd4);

// ////////////////////////////////////////////////////////////////////////// //

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , graph_(nullptr)
    , worker_(new RandDataProducer(DATA_PRODUCER_MIN, DATA_PRODUCER_MAX))
{
    ui_->setupUi(this);
    graph_ = ui_->plot->addGraph();
    graph_->setScatterStyle(QCPScatterStyle::ssDisc);
    graph_->setPen(COLOR_DEFAULT);

    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(worker_.get(), SIGNAL(newData(QVector<double>,QVector<double>)),
            this, SLOT(setPlotData(QVector<double>,QVector<double>)));
    connect(&thread_, &QThread::started, worker_.get(), &RandDataProducer::run);

    worker_->moveToThread(&thread_);
}

// ////////////////////////////////////////////////////////////////////////// //

MainWindow::~MainWindow() {
    worker_->setRunning(false);
    if (thread_.isRunning()) {
        thread_.terminate();
        thread_.wait();
    }
}

// ////////////////////////////////////////////////////////////////////////// //

void MainWindow::setPlotData(QVector<double> x, QVector<double> y) {
    graph_->addData(x, y);
    ui_->plot->rescaleAxes();
    ui_->plot->replot();
}

// ////////////////////////////////////////////////////////////////////////// //

void MainWindow::on_tbStart_pressed() {
    if (thread_.isRunning()) {
        worker_->setPaused( !(worker_->isPaused()));
    } else {
        graph_->data()->clear();
        worker_->setRunning(true);
        thread_.start();
    }
    ui_->tbStart->setEnabled(false);
    ui_->tbPause->setEnabled(true);
    ui_->tbStop->setEnabled(true);
}

// ////////////////////////////////////////////////////////////////////////// //

void MainWindow::on_tbPause_pressed() {
    if (thread_.isRunning()) {
        worker_->setPaused(!(worker_->isPaused()));
        ui_->tbStart->setEnabled(true);
        ui_->tbPause->setEnabled(false);
        ui_->tbStop->setEnabled(true);
    }
}

// ////////////////////////////////////////////////////////////////////////// //

void MainWindow::on_tbStop_pressed() {
    if (thread_.isRunning()) {
        worker_->setRunning(false);
        thread_.terminate();
        ui_->tbStart->setEnabled(true);
        ui_->tbPause->setEnabled(false);
        ui_->tbStop->setEnabled(false);
    }
}

// ////////////////////////////////////////////////////////////////////////// //

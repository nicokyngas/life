#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board_view_qt.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    life::board_view_qt *board = new life::board_view_qt(10, this);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(board, 0, 0, {Qt::AlignTop, Qt::AlignLeft});
    this->setLayout(layout);

    auto sizeWidget = this->findChild<QSpinBox*>("boardDim");
    connect(sizeWidget, SIGNAL(valueChanged(int)), board, SLOT(resize(int)));
    auto nextStateButton = this->findChild<QPushButton*>("goToNextState");
    connect(nextStateButton, SIGNAL(clicked()), board, SLOT(nextState()));
    auto runCB = this->findChild<QCheckBox*>("runCB");

    QTimer *runTimer = new QTimer(runCB);
    runTimer->setInterval(500);
    //connect(runTimer, &QTimer::timeout, board, SLOT(nextState()));
    connect(runTimer, SIGNAL(timeout()), board, SLOT(nextState()));
    connect(runCB, &QCheckBox::toggled, runTimer, [runTimer] (bool checked) {
        if (checked)
        {
            runTimer->start();
        }
        else
        {
            runTimer->stop();
        }
    });
    connect(runCB, &QCheckBox::toggled, nextStateButton, [nextStateButton] (bool checked) {
        nextStateButton->setEnabled(!checked);
    });
    connect(runCB, &QCheckBox::toggled, sizeWidget, [sizeWidget] (bool checked) {
        sizeWidget->setEnabled(!checked);
    });
    this->children();

}

MainWindow::~MainWindow()
{
    delete ui;
}


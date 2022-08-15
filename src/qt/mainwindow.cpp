#include <QTimer>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board_view_qt.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the board view and add it to the UI
    life::board_view_qt *board = new life::board_view_qt(10, this);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(board, 0, 0, {Qt::AlignTop, Qt::AlignLeft});
    this->setLayout(layout);

    // Apply superglue between the various UI elements
    QSpinBox *sizeWidget = this->findChild<QSpinBox*>("boardDim");
    connect(sizeWidget, SIGNAL(valueChanged(int)), board, SLOT(resize(int)));
    QPushButton *nextStateButton = this->findChild<QPushButton*>("goToNextState");
    connect(nextStateButton, SIGNAL(clicked()), board, SLOT(nextState()));
    QCheckBox *runCB = this->findChild<QCheckBox*>("runCB");

    QTimer *runTimer = new QTimer(runCB);
    runTimer->setInterval(500);
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

}

MainWindow::~MainWindow()
{
    delete ui;
}


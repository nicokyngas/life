#ifndef BOARD_VIEW_QT_H
#define BOARD_VIEW_QT_H

#include <QCheckBox>
#include <QGridLayout>
#include <QWidget>
#include "board.h"

namespace life {

    class cell_view_qt : public QWidget
    {
        Q_OBJECT

    public:
        cell_view_qt(const cell *cell, board *board, QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent (QMouseEvent *event) override;
    private:
        const cell *cell;
        board *board;
    };

    class board_view_qt : public QWidget
    {
        Q_OBJECT

        using cell_type = cell_view_qt;

    public:
        board_view_qt(unsigned short size, QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *event) override;
    private:
        board board;
        QGridLayout grid;
        std::vector<std::unique_ptr<cell_type>> cells;

    public slots:
        void resize(int newSize);
        void nextState();
    };

}

#endif // BOARD_VIEW_QT_H

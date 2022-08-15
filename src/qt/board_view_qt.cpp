#include "board_view_qt.h"

namespace life
{

    board_view_qt::board_view_qt(board_dimension_type size, QWidget *parent)
        : QWidget(parent), board(size), grid(this)
    {
        this->grid.setSpacing(1);
        this->setLayout(&grid);
        this->resize(size);
    }

    void board_view_qt::paintEvent(QPaintEvent *event)
    {
        // Must update the child cells, otherwise they won't be repainted
        for (const auto &c : this->cells){
            c->update();
        }
        QWidget::paintEvent(event);
    }

    void board_view_qt::resize(int newSize)
    {
        // Resize board first - references to its new cells are required later.
        this->board.resize(newSize);
        // Remove existing items
        QLayoutItem *child;
        while ((child = this->grid.takeAt(0)) != nullptr) {
            // Ownership of subwidgets is in this->cells
            //  -> clear() deletes the subwidgets
            //  -> remove the layout item but not the subwidget here
            //delete child->widget();
            delete child;
        }
        this->cells.clear();
        // Ensure space and add+format new items
        this->cells.reserve(newSize*newSize);
        for (int i = 0; i < newSize*newSize; ++i){
            const int row = i / newSize;
            const int col = i % newSize;
            this->cells.emplace_back(std::make_unique<cell_type>(&this->board.get(row, col), &this->board, this));
            this->cells[i]->setFixedSize(20, 20);
            this->cells[i]->setAutoFillBackground(true);
            this->grid.addWidget(this->cells[i].get(), row, col);
        }
    }

    void board_view_qt::nextState()
    {
        this->board.nextState();
        this->update();
    }

    cell_view_qt::cell_view_qt(const life::cell *cell, life::board *board, QWidget *parent)
        : QWidget(parent), cell(cell), board(board)
    {
    }

    void cell_view_qt::paintEvent(QPaintEvent *event)
    {
        // Lazily bind to the corresponding cell data to get the right color
        static QPalette black(Qt::black, Qt::black);
        static QPalette white(Qt::white, Qt::white);
        this->setPalette(this->cell->isAlive() ? black : white);
        QWidget::paintEvent(event);
    }

    void cell_view_qt::mousePressEvent(QMouseEvent *event)
    {
        this->board->flip(this->cell->getX(), this->cell->getY());
        this->update();
    }

}

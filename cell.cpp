#include "cell.h"

#include <QDebug>

namespace life
{

    cell::cell(board_dimension_type x, board_dimension_type y, bool alive)
        : x(x), y(y), alive(alive)
    {
    }

    cell cell::nextState(unsigned short aliveNeighbors) const
    {
        bool nextAlive = false;
        if ((this->alive && 2 <= aliveNeighbors && aliveNeighbors <= 3)
        || (!this->alive && aliveNeighbors == 3))
        {
            nextAlive = true;
        }
        return cell(this->x, this->y, nextAlive);
    }

    bool cell::isAlive() const
    {
        return this->alive;
    }

    void cell::flip()
    {
        this->alive = !this->alive;
    }

    board_dimension_type cell::getX() const
    {
        return this->x;
    }

    board_dimension_type cell::getY() const
    {
        return this->y;
    }

}

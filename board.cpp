#include "board.h"

namespace life
{

    board::board(board_dimension_type size)
        : size(size)
    {
        this->cells.reserve(size*size);
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                this->cells.emplace_back(j, i, false);
            }
        }
    }

    void board::nextState()
    {
        // Copy the state of the board, and use the copy as a pristine source
        // to calculate the next state of this.
        board copyBoard(*this);
        for (const auto &cell : this->cells)
        {
            std::vector<const life::cell *> nbs = copyBoard.getNeighbors(cell);
            int aliveCount = 0;
            for (const auto nb : nbs){
                if (nb->isAlive())
                {
                    ++aliveCount;
                }
            }
            this->set(cell.getX(), cell.getY(), cell.nextState(aliveCount));
        }
    }

    const cell& board::get(board_dimension_type x, board_dimension_type y) const
    {
        return this->cells[y*this->size+x];
    }

    void board::set(board_dimension_type x, board_dimension_type y, const cell& cell)
    {
        this->cells[y*this->size+x] = cell;
    }

    void board::flip(board_dimension_type x, board_dimension_type y)
    {
        this->cells[y*this->size+x].flip();
    }

    board_dimension_type board::getSize() const
    {
        return this->size;
    }

    void board::resize(board_dimension_type newSize)
    {
        board newBoard(newSize);
        const int minSize = std::min<int>(this->size, newSize);
        for (int i = 0; i < minSize; ++i){
            for (int j = 0; j < minSize; ++j){
                newBoard.set(j, i, this->get(j, i));
            }
        }
        *this = newBoard;
    }

    std::vector<const cell *> board::getNeighbors(const cell &cell) const
    {
        std::vector<const life::cell*> nbs;
        // 8 is a trivial and good enough upper bound on the number of neighbors
        nbs.reserve(8);
        for (int i = -1; i <= 1; ++i){
            if ((i < 0 && cell.getY() == 0)
             || (i > 0 && cell.getY() == size - 1))
            {
                continue;
            }
            for (int j = -1; j <= 1; ++j){
                if ((j < 0 && cell.getX() == 0)
                 || (j > 0 && cell.getX() == size - 1)
                 || (j == 0 && i == 0))
                {
                    continue;
                }
                nbs.emplace_back(&(this->get(cell.getX()+j, cell.getY()+i)));
            }
        }
        return nbs;
    }

}

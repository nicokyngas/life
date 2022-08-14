#include "board.h"

namespace life {

    board::board(unsigned short size)
        : size(size)
    {
        this->cells.reserve(size*size);
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                this->cells.emplace_back(j, i, false);
            }
        }
    }

    board board::nextState()
    {
        board copyBoard(*this);
        for (const auto &cell : this->cells)
        {
            std::vector<const life::cell *> nbs = copyBoard.getNeighbors(cell);
            int aliveCount = 0;
            for (const auto nb : nbs){
                if (nb->alive)
                {
                    ++aliveCount;
                }
            }
            this->set(cell.x, cell.y, cell.nextState(aliveCount));
        }
        return *this;
    }

    const cell& board::get(unsigned short x, unsigned short y) const
    {
        return this->cells[y*this->size+x];
    }

    void board::set(unsigned short x, unsigned short y, const cell& cell)
    {
        this->cells[y*this->size+x] = cell;
    }

    void board::flip(unsigned short x, unsigned short y)
    {
        this->cells[y*this->size+x].flip();
    }

    unsigned short board::getSize() const
    {
        return this->size;
    }

    void board::resize(unsigned short newSize)
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
        nbs.reserve(8);
        for (int i = -1; i <= 1; ++i){
            if ((i < 0 && cell.y == 0)
             || (i > 0 && cell.y == size - 1))
            {
                continue;
            }
            for (int j = -1; j <= 1; ++j){
                if ((j < 0 && cell.x == 0)
                 || (j > 0 && cell.x == size - 1)
                 || (j == 0 && i == 0))
                {
                    continue;
                }
                nbs.emplace_back(&(this->get(cell.x+j, cell.y+i)));
            }
        }
        return nbs;
    }

}

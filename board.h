#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"

namespace life {

    class board
    {
    public:
        board() = delete;
        board(unsigned short size);
        board nextState();
        const cell& get(unsigned short x, unsigned short y) const;
        void set(unsigned short x, unsigned short y, const cell& cell);
        void flip(unsigned short x, unsigned short y);
        unsigned short getSize() const;
        void resize(unsigned short newSize);
    private:
        std::vector<const cell*> getNeighbors(const cell &cell) const;

        unsigned short size;
        std::vector<cell> cells;
    };

}

#endif // BOARD_H

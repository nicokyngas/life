#ifndef CELL_H
#define CELL_H

namespace life {

    class cell
    {

    public:
        cell() = delete;
        cell(unsigned short x, unsigned short y, bool alive);
        cell nextState(unsigned short aliveNeighbors) const;
        bool isAlive() const;
        void flip();
        unsigned short getX() const;
        unsigned short getY() const;
    private:
        unsigned short x;
        unsigned short y;
        bool alive;

        friend class board;
    };

}

#endif // CELL_H

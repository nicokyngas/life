/**
 * @file cell.h
 *
 * @brief Header for the model of a cell of a board in Game of Life
 *
 */

#ifndef CELL_H
#define CELL_H

#include "definitions.h"

namespace life {

    /**
     * @brief A binary state on a n x n board
     */
    class cell
    {

    public:
        /**
         * @brief Explicitly deleted default constructor for safety
         */
        cell() = delete;
        /**
         * @brief Construct a new cell
         * @param x x-coordinate
         * @param y y-coordinate
         * @param alive Is the cell alive or not
         */
        cell(board_dimension_type x, board_dimension_type y, bool alive);
        /**
         * @brief Calculate and return the next state of the cell according to the
         *   number of neighbors alive and the rules of Game of Life
         * @param aliveNeighbors The number of neighbors that are alive
         * @return The calculated state
         */
        cell nextState(unsigned short aliveNeighbors) const;
        /**
         * @return Is this cell alive?
         */
        bool isAlive() const;
        /**
         * @brief If the cell is alive, kill it. If the cell is dead, raise it.
         */
        void flip();
        /**
         * @return The x-coordinate of the cell
         */
        board_dimension_type getX() const;
        /**
         * @return The y-coordinate of the cell
         */
        board_dimension_type getY() const;
    private:
        board_dimension_type x;
        board_dimension_type y;
        bool alive;
    };

}

#endif // CELL_H

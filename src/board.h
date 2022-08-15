/**
 * @file board.h
 *
 * @brief Header for the model of a board of Game of Life
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include "definitions.h"

namespace life
{

    /**
     * @brief An n x n board of binary states
     */
    class board
    {
    public:
        /**
         * @brief Explicitly deleted default constructor for safety
         */
        board() = delete;
        /**
         * @brief Construct an empty board of size x size
         * @param The number of cells per side of the board
         */
        board(board_dimension_type size);
        /**
         * @brief Mutate the board to the next state according to the rules of Game of Life
         */
        void nextState();
        /**
         * @brief Return the cell at the given coordinates of the board
         * @param x x-coordinate in [0, size-1]
         * @param y y-coordinate in [0, size-1]
         * @return The desired (immutable) cell
         */
        const cell& get(board_dimension_type x, board_dimension_type y) const;
        /**
         * @brief Set the cell at the given coordinates of the board
         * @param x x-coordinate in [0, size-1]
         * @param y y-coordinate in [0, size-1]
         * @param cell The new state of the cell
         */
        void set(board_dimension_type x, board_dimension_type y, const cell& cell);
        /**
         * @brief Invert the state of the given cell
         * @param x x-coordinate in [0, size-1]
         * @param y y-coordinate in [0, size-1]
         */
        void flip(board_dimension_type x, board_dimension_type y);
        /**
         * @return The number of cells per side of the board
         */
        board_dimension_type getSize() const;
        /**
         * @brief Resize the board to the given size.
         *   If newSize < size, cells are removed from below and the right.
         *   If newSize > size, empty cells are added to the right and below.
         * @param newSize The new number of cells per side of the board
         */
        void resize(board_dimension_type newSize);
    private:
        /**
         * @brief Return the cells immediately adjacent to the given cell.
         *   Adjacency is considered also diagonally, yielding a maximum
         *   of eight neighbours per cell.
         * @param cell The cell whose neighbors should be considered
         * @return A list of the neighboring cells
         */
        std::vector<const cell*> getNeighbors(const cell &cell) const;

        /**
         * @brief The number of cells per side of the board
         */
        board_dimension_type size;
        /**
         * @brief A one-dimensional row-major vector of the cells of the board
         */
        std::vector<cell> cells;
    };

}

#endif // BOARD_H

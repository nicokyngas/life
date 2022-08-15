/**
 * @file board_view_qt.h
 *
 * @brief Header for the view of a board
 *
 */

#ifndef BOARD_VIEW_QT_H
#define BOARD_VIEW_QT_H

#include <QGridLayout>
#include <QWidget>
#include "board.h"

namespace life
{

    /**
     * @brief View of a single cell of a board
     */
    class cell_view_qt : public QWidget
    {
        Q_OBJECT

    public:
        /**
         * @brief Constructs the view for a given cell
         * @param cell The cell to be displayed
         * @param board The board owning the cell to be displayed
         * @param parent Parent component of the view on the UI
         */
        cell_view_qt(const cell *cell, board *board, QWidget *parent = nullptr);
    protected:
        /**
         * @brief Paints the cell black or white, depending on the state of the
         *   corresponding cell's alive status
         * @param event Info on the origination of the event
         */
        void paintEvent(QPaintEvent *event) override;
        /**
         * @brief Change the status of the corresponding cell's alive status
         * @param event Info on the origination of the event
         */
        void mousePressEvent (QMouseEvent *event) override;
    private:
        /**
         * @brief The corresponding cell whose alive status this view displays
         */
        const cell *cell;
        /**
         * @brief The board that owns cell
         */
        board *board;
    };

    /**
     * @brief View and model of a board
     */
    class board_view_qt : public QWidget
    {
        Q_OBJECT

        using cell_type = cell_view_qt;

    public:
        /**
         * @brief Constructs a view for a board of given size
         * @param size The number of cells per side of the board
         * @param parent Parent component of the view on the UI
         */
        board_view_qt(board_dimension_type size, QWidget *parent = nullptr);
    protected:
        /**
         * @brief Displays the board
         * @param event Info on the origination of the event
         */
        void paintEvent(QPaintEvent *event) override;
    private:
        /**
         * @brief The board this view is displaying
         */
        board board;
        /**
         * @brief Layout used to display the cells of the board
         */
        QGridLayout grid;
        /**
         * @brief List of singular cell views that make up the board
         */
        std::vector<std::unique_ptr<cell_type>> cells;

    public slots:
        /**
         * @brief resize Resize both the view and the board
         * @param newSize The new number of cells per side of the board
         */
        void resize(int newSize);
        /**
         * @brief Move the underlying board to its next state according to the rules
         *   of Game of Life
         */
        void nextState();
    };

}

#endif // BOARD_VIEW_QT_H

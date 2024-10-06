#include <iostream>
#include <cctype>
#include <string>
#include "boop.h"
#include "colors.h"

using namespace std;

/**
 * @brief basic constructor for Boop class
 * initializes a blank board and sets original
 * number of player pieces
 */
Boop::Boop()
{
    restart();
}

/**
 * @brief restarts board and game to initial setup
 */
void Boop::restart()
{
    // players start with zero frogs
    p1_frogs = 0;
    p2_frogs = 0;
    // players start with 8 tadpoles
    p1_tadpoles = 8;
    p2_tadpoles = 8;

    move_type = 0;
    move_options.clear();

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j].make_blank();
        }
    }
    game::restart();
}

/**
 * @brief update the board, piece count, and move count
 * based on a player's move
 *
 * @param move the move string of the player
 */
void Boop::make_move(const string &move)
{
    // cast all of the move characters to useable values
    char piece = move[0];
    int column = int(toupper(move[1]) - 'A');
    int row = move[2] - '1';

    // if the move is standard
    if (move_type == 0)
    {
        if (piece == 'f' || piece == 'F')
        {
            if (next_mover() == HUMAN)
            {
                p1_frogs--;
                board[row][column].make_frog(1);
            }
            else if (next_mover() == COMPUTER)
            {
                p2_frogs--;
                board[row][column].make_frog(2);
            }

            // BOOPING TIME FOR FROGS
            if (row != 0) // don't walk off the board TOP
            {
                if (board[row - 1][column].get_state() != "blank") // if TOP space is occupied
                {
                    if (row == 1) // if at the TOP of the board, BOOP OFF
                    {
                        if (board[row - 1][column].get_player() == 1)
                        {
                            if (board[row - 1][column].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row - 1][column].make_blank();
                            }
                            else if (board[row - 1][column].get_state() == "frog")
                            {
                                p1_frogs++;
                                board[row - 1][column].make_blank();
                            }
                        }
                        if (board[row - 1][column].get_player() == 2)
                        {
                            if (board[row - 1][column].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row - 1][column].make_blank();
                            }
                            else if (board[row - 1][column].get_state() == "frog")
                            {
                                p2_frogs++;
                                board[row - 1][column].make_blank();
                            }
                        }
                    }
                    else // if not at the TOP of board
                    {
                        if (board[row - 2][column].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row - 1][column].get_player() == 1)
                            {
                                if (board[row - 1][column].get_state() == "tadpole")
                                {
                                    board[row - 1][column].make_blank();
                                    board[row - 2][column].make_tadpole(1);
                                }
                                else if (board[row - 1][column].get_state() == "frog")
                                {
                                    board[row - 1][column].make_blank();
                                    board[row - 2][column].make_frog(1);
                                }
                            }
                            else if (board[row - 1][column].get_player() == 2)
                            {
                                if (board[row - 1][column].get_state() == "tadpole")
                                {
                                    board[row - 1][column].make_blank();
                                    board[row - 2][column].make_tadpole(2);
                                }
                                else if (board[row - 1][column].get_state() == "frog")
                                {
                                    board[row - 1][column].make_blank();
                                    board[row - 2][column].make_frog(2);
                                }
                            }
                        }
                    }
                }
                if (column != 0) // don't walk off the board TOP LEFT
                {
                    if (board[row - 1][column - 1].get_state() != "blank") // if TOP LEFT space is occupied
                    {
                        if (row == 1 || column == 1) // if at the TOP LEFT corner of the board OR the TOP edge OR the LEFT edge, BOOP OFF
                        {
                            if (board[row - 1][column - 1].get_player() == 1)
                            {
                                if (board[row - 1][column - 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row - 1][column - 1].make_blank();
                                }
                                else if (board[row - 1][column - 1].get_state() == "frog")
                                {
                                    p1_frogs++;
                                    board[row - 1][column - 1].make_blank();
                                }
                            }
                            if (board[row - 1][column - 1].get_player() == 2)
                            {
                                if (board[row - 1][column - 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row - 1][column - 1].make_blank();
                                }
                                else if (board[row - 1][column - 1].get_state() == "frog")
                                {
                                    p2_frogs++;
                                    board[row - 1][column - 1].make_blank();
                                }
                            }
                        }
                        else // if not at the TOP/LEFT of the board
                        {
                            if (board[row - 2][column - 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row - 1][column - 1].get_player() == 1)
                                {
                                    if (board[row - 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column - 1].make_blank();
                                        board[row - 2][column - 2].make_tadpole(1);
                                    }
                                    else if (board[row - 1][column - 1].get_state() == "frog")
                                    {
                                        board[row - 1][column - 1].make_blank();
                                        board[row - 2][column - 2].make_frog(1);
                                    }
                                }
                                else if (board[row - 1][column - 1].get_player() == 2)
                                {
                                    if (board[row - 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column - 1].make_blank();
                                        board[row - 2][column - 2].make_tadpole(2);
                                    }
                                    else if (board[row - 1][column - 1].get_state() == "frog")
                                    {
                                        board[row - 1][column - 1].make_blank();
                                        board[row - 2][column - 2].make_frog(2);
                                    }
                                }
                            }
                        }
                    }
                }
                if (column != 5) // don't walk off the board TOP RIGHT
                {
                    if (board[row - 1][column + 1].get_state() != "blank") // if TOP RIGHT space is occupied
                    {
                        if (row == 1 || column == 4) // if at the TOP RIGHT corner OR the TOP edge OR the RIGHT edge of the board, BOOP OFF
                        {
                            if (board[row - 1][column + 1].get_player() == 1)
                            {
                                if (board[row - 1][column + 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row - 1][column + 1].make_blank();
                                }
                                else if (board[row - 1][column + 1].get_state() == "frog")
                                {
                                    p1_frogs++;
                                    board[row - 1][column + 1].make_blank();
                                }
                            }
                            if (board[row - 1][column + 1].get_player() == 2)
                            {
                                if (board[row - 1][column + 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row - 1][column + 1].make_blank();
                                }
                                else if (board[row - 1][column + 1].get_state() == "frog")
                                {
                                    p2_frogs++;
                                    board[row - 1][column + 1].make_blank();
                                }
                            }
                        }
                        else // if not at the TOP/RIGHT of the board
                        {
                            if (board[row - 2][column + 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row - 1][column + 1].get_player() == 1)
                                {
                                    if (board[row - 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column + 1].make_blank();
                                        board[row - 2][column + 2].make_tadpole(1);
                                    }
                                    else if (board[row - 1][column + 1].get_state() == "frog")
                                    {
                                        board[row - 1][column + 1].make_blank();
                                        board[row - 2][column + 2].make_frog(1);
                                    }
                                }
                                else if (board[row - 1][column + 1].get_player() == 2)
                                {
                                    if (board[row - 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column + 1].make_blank();
                                        board[row - 2][column + 2].make_tadpole(2);
                                    }
                                    else if (board[row - 1][column + 1].get_state() == "frog")
                                    {
                                        board[row - 1][column + 1].make_blank();
                                        board[row - 2][column + 2].make_frog(2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (row != 5) // don't walk off the board BOTTOM
            {
                if (board[row + 1][column].get_state() != "blank") // if BOTTOM space is occupied
                {
                    if (row == 4) // if at the BOTTOM edge of the board
                    {
                        if (board[row + 1][column].get_player() == 1)
                        {
                            if (board[row + 1][column].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row + 1][column].make_blank();
                            }
                            else if (board[row + 1][column].get_state() == "frog")
                            {
                                p1_frogs++;
                                board[row + 1][column].make_blank();
                            }
                        }
                        if (board[row + 1][column].get_player() == 2)
                        {
                            if (board[row + 1][column].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row + 1][column].make_blank();
                            }
                            else if (board[row + 1][column].get_state() == "frog")
                            {
                                p2_frogs++;
                                board[row + 1][column].make_blank();
                            }
                        }
                    }
                    else // if not at the BOTTOM edge of board
                    {
                        if (board[row + 2][column].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row + 1][column].get_player() == 1)
                            {
                                if (board[row + 1][column].get_state() == "tadpole")
                                {
                                    board[row + 1][column].make_blank();
                                    board[row + 2][column].make_tadpole(1);
                                }
                                else if (board[row + 1][column].get_state() == "frog")
                                {
                                    board[row + 1][column].make_blank();
                                    board[row + 2][column].make_frog(1);
                                }
                            }
                            else if (board[row + 1][column].get_player() == 2)
                            {
                                if (board[row + 1][column].get_state() == "tadpole")
                                {
                                    board[row + 1][column].make_blank();
                                    board[row + 2][column].make_tadpole(2);
                                }
                                else if (board[row + 1][column].get_state() == "frog")
                                {
                                    board[row + 1][column].make_blank();
                                    board[row + 2][column].make_frog(2);
                                }
                            }
                        }
                    }
                }
                if (column != 0) // don't walk off the board BOTTOM LEFT
                {
                    if (board[row + 1][column - 1].get_state() != "blank") // if BOTTOM LEFT space is occupied
                    {
                        if (row == 4 || column == 1) // if at the BOTTOM LEFT corner OR the BOTTOM edge OR the LEFT edge of the board, BOOP OFF
                        {
                            if (board[row + 1][column - 1].get_player() == 1)
                            {
                                if (board[row + 1][column - 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row + 1][column - 1].make_blank();
                                }
                                else if (board[row + 1][column - 1].get_state() == "frog")
                                {
                                    p1_frogs++;
                                    board[row + 1][column - 1].make_blank();
                                }
                            }
                            if (board[row + 1][column - 1].get_player() == 2)
                            {
                                if (board[row + 1][column - 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row + 1][column - 1].make_blank();
                                }
                                else if (board[row + 1][column - 1].get_state() == "frog")
                                {
                                    p2_frogs++;
                                    board[row + 1][column - 1].make_blank();
                                }
                            }
                        }
                        else // if not at the BOTTOM/LEFT edge of the board
                        {
                            if (board[row + 2][column - 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row + 1][column - 1].get_player() == 1)
                                {
                                    if (board[row + 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column - 1].make_blank();
                                        board[row + 2][column - 2].make_tadpole(1);
                                    }
                                    else if (board[row + 1][column - 1].get_state() == "frog")
                                    {
                                        board[row + 1][column - 1].make_blank();
                                        board[row + 2][column - 2].make_frog(1);
                                    }
                                }
                                else if (board[row + 1][column - 1].get_player() == 2)
                                {
                                    if (board[row + 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column - 1].make_blank();
                                        board[row + 2][column - 2].make_tadpole(2);
                                    }
                                    else if (board[row + 1][column - 1].get_state() == "frog")
                                    {
                                        board[row + 1][column - 1].make_blank();
                                        board[row + 2][column - 2].make_frog(2);
                                    }
                                }
                            }
                        }
                    }
                }
                if (column != 5) // don't walk off the board BOTTOM RIGHT
                {
                    if (board[row + 1][column + 1].get_state() != "blank") // if BOTTOM RIGHT space is occupied
                    {
                        if (row == 4 || column == 4) // if at the BOTTOM RIGHT corner OR the BOTTOM edge OR the RIGHT edge of the board, BOOP OFF
                        {
                            if (board[row + 1][column + 1].get_player() == 1)
                            {
                                if (board[row + 1][column + 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row + 1][column + 1].make_blank();
                                }
                                else if (board[row + 1][column + 1].get_state() == "frog")
                                {
                                    p1_frogs++;
                                    board[row + 1][column + 1].make_blank();
                                }
                            }
                            if (board[row + 1][column + 1].get_player() == 2)
                            {
                                if (board[row + 1][column + 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row + 1][column + 1].make_blank();
                                }
                                else if (board[row + 1][column + 1].get_state() == "frog")
                                {
                                    p2_frogs++;
                                    board[row + 1][column + 1].make_blank();
                                }
                            }
                        }
                        else // if not at the BOTTOM/RIGHT of the board
                        {
                            if (board[row + 2][column + 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row + 1][column + 1].get_player() == 1)
                                {
                                    if (board[row + 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column + 1].make_blank();
                                        board[row + 2][column + 2].make_tadpole(1);
                                    }
                                    else if (board[row + 1][column + 1].get_state() == "frog")
                                    {
                                        board[row + 1][column + 1].make_blank();
                                        board[row + 2][column + 2].make_frog(1);
                                    }
                                }
                                else if (board[row + 1][column + 1].get_player() == 2)
                                {
                                    if (board[row + 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column + 1].make_blank();
                                        board[row + 2][column + 2].make_tadpole(2);
                                    }
                                    else if (board[row + 1][column + 1].get_state() == "frog")
                                    {
                                        board[row + 1][column + 1].make_blank();
                                        board[row + 2][column + 2].make_frog(2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (column != 0) // don't walk off the board LEFT
            {
                if (board[row][column - 1].get_state() != "blank") // if LEFT space is occupied
                {
                    if (column == 1) // if at the LEFT edge of the board, BOOP OFF
                    {
                        if (board[row][column - 1].get_player() == 1)
                        {
                            if (board[row][column - 1].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row][column - 1].make_blank();
                            }
                            else if (board[row][column - 1].get_state() == "frog")
                            {
                                p1_frogs++;
                                board[row][column - 1].make_blank();
                            }
                        }
                        if (board[row][column - 1].get_player() == 2)
                        {
                            if (board[row][column - 1].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row][column - 1].make_blank();
                            }
                            else if (board[row][column - 1].get_state() == "frog")
                            {
                                p2_frogs++;
                                board[row][column - 1].make_blank();
                            }
                        }
                    }
                    else // if not at the LEFT edge of board
                    {
                        if (board[row][column - 2].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row][column - 1].get_player() == 1)
                            {
                                if (board[row][column - 1].get_state() == "tadpole")
                                {
                                    board[row][column - 1].make_blank();
                                    board[row][column - 2].make_tadpole(1);
                                }
                                else if (board[row][column - 1].get_state() == "frog")
                                {
                                    board[row][column - 1].make_blank();
                                    board[row][column - 2].make_frog(1);
                                }
                            }
                            else if (board[row][column - 1].get_player() == 2)
                            {
                                if (board[row][column - 1].get_state() == "tadpole")
                                {
                                    board[row][column - 1].make_blank();
                                    board[row][column - 2].make_tadpole(2);
                                }
                                else if (board[row][column - 1].get_state() == "frog")
                                {
                                    board[row][column - 1].make_blank();
                                    board[row][column - 2].make_frog(2);
                                }
                            }
                        }
                    }
                }
            }
            if (column != 5) // don't walk off the board RIGHT
            {
                if (board[row][column + 1].get_state() != "blank") // if RIGHT space is occupied
                {
                    if (column == 4) // if at the RIGHT edge of the board, BOOP
                    {
                        if (board[row][column + 1].get_player() == 1)
                        {
                            if (board[row][column + 1].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row][column + 1].make_blank();
                            }
                            else if (board[row][column + 1].get_state() == "frog")
                            {
                                p1_frogs++;
                                board[row][column + 1].make_blank();
                            }
                        }
                        if (board[row][column + 1].get_player() == 2)
                        {
                            if (board[row][column + 1].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row][column + 1].make_blank();
                            }
                            else if (board[row][column + 1].get_state() == "frog")
                            {
                                p2_frogs++;
                                board[row][column + 1].make_blank();
                            }
                        }
                    }
                    else // if not at the RIGHT edge of board
                    {
                        if (board[row][column + 2].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row][column + 1].get_player() == 1)
                            {
                                if (board[row][column + 1].get_state() == "tadpole")
                                {
                                    board[row][column + 1].make_blank();
                                    board[row][column + 2].make_tadpole(1);
                                }
                                else if (board[row][column + 1].get_state() == "frog")
                                {
                                    board[row][column + 1].make_blank();
                                    board[row][column + 2].make_frog(1);
                                }
                            }
                            else if (board[row][column + 1].get_player() == 2)
                            {
                                if (board[row][column + 1].get_state() == "tadpole")
                                {
                                    board[row][column + 1].make_blank();
                                    board[row][column + 2].make_tadpole(2);
                                }
                                else if (board[row][column + 1].get_state() == "frog")
                                {
                                    board[row][column + 1].make_blank();
                                    board[row][column + 2].make_frog(2);
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (piece == 't' || piece == 'T')
        {
            if (next_mover() == HUMAN)
            {
                p1_tadpoles--;
                board[row][column].make_tadpole(1);
            }
            else if (next_mover() == COMPUTER)
            {
                p2_tadpoles--;
                board[row][column].make_tadpole(2);
            }

            // BOOPING TIME FOR TADPOLES
            if (row != 0) // don't walk off the board TOP
            {
                if (board[row - 1][column].get_state() != "blank") // if TOP space is occupied
                {
                    if (row == 1) // if at the TOP of the board, BOOP OFF
                    {
                        if (board[row - 1][column].get_player() == 1)
                        {
                            if (board[row - 1][column].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row - 1][column].make_blank();
                            }
                        }
                        if (board[row - 1][column].get_player() == 2)
                        {
                            if (board[row - 1][column].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row - 1][column].make_blank();
                            }
                            else if (board[row - 1][column].get_state() == "frog")
                            {
                                p2_frogs++;
                                board[row - 1][column].make_blank();
                            }
                        }
                    }
                    else // if not at the TOP of board
                    {
                        if (board[row - 2][column].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row - 1][column].get_player() == 1)
                            {
                                if (board[row - 1][column].get_state() == "tadpole")
                                {
                                    board[row - 1][column].make_blank();
                                    board[row - 2][column].make_tadpole(1);
                                }
                            }
                            else if (board[row - 1][column].get_player() == 2)
                            {
                                if (board[row - 1][column].get_state() == "tadpole")
                                {
                                    board[row - 1][column].make_blank();
                                    board[row - 2][column].make_tadpole(2);
                                }
                            }
                        }
                    }
                }
                if (column != 0) // don't walk off the board TOP LEFT
                {
                    if (board[row - 1][column - 1].get_state() != "blank") // if TOP LEFT space is occupied
                    {
                        if (row == 1 || column == 1) // if at the TOP LEFT corner of the board OR the TOP edge OR the LEFT edge, BOOP OFF
                        {
                            if (board[row - 1][column - 1].get_player() == 1)
                            {
                                if (board[row - 1][column - 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row - 1][column - 1].make_blank();
                                }
                            }
                            if (board[row - 1][column - 1].get_player() == 2)
                            {
                                if (board[row - 1][column - 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row - 1][column - 1].make_blank();
                                }
                            }
                        }
                        else // if not at the TOP/LEFT of the board
                        {
                            if (board[row - 2][column - 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row - 1][column - 1].get_player() == 1)
                                {
                                    if (board[row - 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column - 1].make_blank();
                                        board[row - 2][column - 2].make_tadpole(1);
                                    }
                                }
                                else if (board[row - 1][column - 1].get_player() == 2)
                                {
                                    if (board[row - 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column - 1].make_blank();
                                        board[row - 2][column - 2].make_tadpole(2);
                                    }
                                }
                            }
                        }
                    }
                }
                if (column != 5) // don't walk off the board TOP RIGHT
                {
                    if (board[row - 1][column + 1].get_state() != "blank") // if TOP RIGHT space is occupied
                    {
                        if (row == 1 || column == 4) // if at the TOP RIGHT corner OR the TOP edge OR the RIGHT edge of the board, BOOP OFF
                        {
                            if (board[row - 1][column + 1].get_player() == 1)
                            {
                                if (board[row - 1][column + 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row - 1][column + 1].make_blank();
                                }
                            }
                            if (board[row - 1][column + 1].get_player() == 2)
                            {
                                if (board[row - 1][column + 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row - 1][column + 1].make_blank();
                                }
                            }
                        }
                        else // if not at the TOP/RIGHT of the board
                        {
                            if (board[row - 2][column + 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row - 1][column + 1].get_player() == 1)
                                {
                                    if (board[row - 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column + 1].make_blank();
                                        board[row - 2][column + 2].make_tadpole(1);
                                    }
                                }
                                else if (board[row - 1][column + 1].get_player() == 2)
                                {
                                    if (board[row - 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row - 1][column + 1].make_blank();
                                        board[row - 2][column + 2].make_tadpole(2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (row != 5) // don't walk off the board BOTTOM
            {
                if (board[row + 1][column].get_state() != "blank") // if BOTTOM space is occupied
                {
                    if (row == 4) // if at the BOTTOM edge of the board
                    {
                        if (board[row + 1][column].get_player() == 1)
                        {
                            if (board[row + 1][column].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row + 1][column].make_blank();
                            }
                        }
                        if (board[row + 1][column].get_player() == 2)
                        {
                            if (board[row + 1][column].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row + 1][column].make_blank();
                            }
                        }
                    }
                    else // if not at the BOTTOM edge of board
                    {
                        if (board[row + 2][column].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row + 1][column].get_player() == 1)
                            {
                                if (board[row + 1][column].get_state() == "tadpole")
                                {
                                    board[row + 1][column].make_blank();
                                    board[row + 2][column].make_tadpole(1);
                                }
                            }
                            else if (board[row + 1][column].get_player() == 2)
                            {
                                if (board[row + 1][column].get_state() == "tadpole")
                                {
                                    board[row + 1][column].make_blank();
                                    board[row + 2][column].make_tadpole(2);
                                }
                            }
                        }
                    }
                }
                if (column != 0) // don't walk off the board BOTTOM LEFT
                {
                    if (board[row + 1][column - 1].get_state() != "blank") // if BOTTOM LEFT space is occupied
                    {
                        if (row == 4 || column == 1) // if at the BOTTOM LEFT corner OR the BOTTOM edge OR the LEFT edge of the board, BOOP OFF
                        {
                            if (board[row + 1][column - 1].get_player() == 1)
                            {
                                if (board[row + 1][column - 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row + 1][column - 1].make_blank();
                                }
                            }
                            if (board[row + 1][column - 1].get_player() == 2)
                            {
                                if (board[row + 1][column - 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row + 1][column - 1].make_blank();
                                }
                            }
                        }
                        else // if not at the BOTTOM/LEFT edge of the board
                        {
                            if (board[row + 2][column - 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row + 1][column - 1].get_player() == 1)
                                {
                                    if (board[row + 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column - 1].make_blank();
                                        board[row + 2][column - 2].make_tadpole(1);
                                    }
                                }
                                else if (board[row + 1][column - 1].get_player() == 2)
                                {
                                    if (board[row + 1][column - 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column - 1].make_blank();
                                        board[row + 2][column - 2].make_tadpole(2);
                                    }
                                }
                            }
                        }
                    }
                }
                if (column != 5) // don't walk off the board BOTTOM RIGHT
                {
                    if (board[row + 1][column + 1].get_state() != "blank") // if BOTTOM RIGHT space is occupied
                    {
                        if (row == 4 || column == 4) // if at the BOTTOM RIGHT corner OR the BOTTOM edge OR the RIGHT edge of the board, BOOP OFF
                        {
                            if (board[row + 1][column + 1].get_player() == 1)
                            {
                                if (board[row + 1][column + 1].get_state() == "tadpole")
                                {
                                    p1_tadpoles++;
                                    board[row + 1][column + 1].make_blank();
                                }
                            }
                            if (board[row + 1][column + 1].get_player() == 2)
                            {
                                if (board[row + 1][column + 1].get_state() == "tadpole")
                                {
                                    p2_tadpoles++;
                                    board[row + 1][column + 1].make_blank();
                                }
                            }
                        }
                        else // if not at the BOTTOM/RIGHT of the board
                        {
                            if (board[row + 2][column + 2].get_state() == "blank") // if there is room, BOOP
                            {
                                if (board[row + 1][column + 1].get_player() == 1)
                                {
                                    if (board[row + 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column + 1].make_blank();
                                        board[row + 2][column + 2].make_tadpole(1);
                                    }
                                }
                                else if (board[row + 1][column + 1].get_player() == 2)
                                {
                                    if (board[row + 1][column + 1].get_state() == "tadpole")
                                    {
                                        board[row + 1][column + 1].make_blank();
                                        board[row + 2][column + 2].make_tadpole(2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (column != 0) // don't walk off the board LEFT
            {
                if (board[row][column - 1].get_state() != "blank") // if LEFT space is occupied
                {
                    if (column == 1) // if at the LEFT edge of the board, BOOP OFF
                    {
                        if (board[row][column - 1].get_player() == 1)
                        {
                            if (board[row][column - 1].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row][column - 1].make_blank();
                            }
                        }
                        if (board[row][column - 1].get_player() == 2)
                        {
                            if (board[row][column - 1].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row][column - 1].make_blank();
                            }
                        }
                    }
                    else // if not at the LEFT edge of board
                    {
                        if (board[row][column - 2].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row][column - 1].get_player() == 1)
                            {
                                if (board[row][column - 1].get_state() == "tadpole")
                                {
                                    board[row][column - 1].make_blank();
                                    board[row][column - 2].make_tadpole(1);
                                }
                            }
                            else if (board[row][column - 1].get_player() == 2)
                            {
                                if (board[row][column - 1].get_state() == "tadpole")
                                {
                                    board[row][column - 1].make_blank();
                                    board[row][column - 2].make_tadpole(2);
                                }
                            }
                        }
                    }
                }
            }
            if (column != 5) // don't walk off the board RIGHT
            {
                if (board[row][column + 1].get_state() != "blank") // if RIGHT space is occupied
                {
                    if (column == 4) // if at the RIGHT edge of the board, BOOP
                    {
                        if (board[row][column + 1].get_player() == 1)
                        {
                            if (board[row][column + 1].get_state() == "tadpole")
                            {
                                p1_tadpoles++;
                                board[row][column + 1].make_blank();
                            }
                        }
                        if (board[row][column + 1].get_player() == 2)
                        {
                            if (board[row][column + 1].get_state() == "tadpole")
                            {
                                p2_tadpoles++;
                                board[row][column + 1].make_blank();
                            }
                        }
                    }
                    else // if not at the RIGHT edge of board
                    {
                        if (board[row][column + 2].get_state() == "blank") // if there is room, BOOP
                        {
                            if (board[row][column + 1].get_player() == 1)
                            {
                                if (board[row][column + 1].get_state() == "tadpole")
                                {
                                    board[row][column + 1].make_blank();
                                    board[row][column + 2].make_tadpole(1);
                                }
                            }
                            else if (board[row][column + 1].get_player() == 2)
                            {
                                if (board[row][column + 1].get_state() == "tadpole")
                                {
                                    board[row][column + 1].make_blank();
                                    board[row][column + 2].make_tadpole(2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (move_type == 1)
    {
        string direction;
        direction = move.substr(3);

        if (next_mover() == HUMAN)
        {
            p1_frogs++;
            board[row][column].make_blank();
        }
        else if (next_mover() == COMPUTER)
        {
            p2_frogs++;
            board[row][column].make_blank();
        }
        if (direction == "right")
        {
            if (next_mover() == HUMAN)
            {
                p1_frogs++;
                board[row][column + 1].make_blank();
                p1_frogs++;
                board[row][column + 2].make_blank();
            }
            else if (next_mover() == COMPUTER)
            {
                p2_frogs++;
                board[row][column + 1].make_blank();
                p2_frogs++;
                board[row][column + 2].make_blank();
            }
        }
        else if (direction == "down")
        {
            if (next_mover() == HUMAN)
            {
                p1_frogs++;
                board[row + 1][column].make_blank();
                p1_frogs++;
                board[row + 2][column].make_blank();
            }
            else if (next_mover() == COMPUTER)
            {
                p2_frogs++;
                board[row + 1][column].make_blank();
                p2_frogs++;
                board[row + 2][column].make_blank();
            }
        }
        else if (direction == "diagonal right")
        {
            if (next_mover() == HUMAN)
            {
                p1_frogs++;
                board[row + 1][column + 1].make_blank();
                p1_frogs++;
                board[row + 2][column + 2].make_blank();
            }
            else if (next_mover() == COMPUTER)
            {
                p2_frogs++;
                board[row + 1][column + 1].make_blank();
                p2_frogs++;
                board[row + 2][column + 2].make_blank();
            }
        }
        else if (direction == "diagonal left")
        {
            if (next_mover() == HUMAN)
            {
                p1_frogs++;
                board[row + 1][column - 1].make_blank();
                p1_frogs++;
                board[row + 2][column - 2].make_blank();
            }
            else if (next_mover() == COMPUTER)
            {
                p2_frogs++;
                board[row + 1][column - 1].make_blank();
                p2_frogs++;
                board[row + 2][column - 2].make_blank();
            }
        }
        game::make_move(move);
    }
    else if (move_type == 2)
    {
        if (next_mover() == HUMAN)
        {
            p1_frogs++;
            board[row][column].make_blank();
        }
        else if (next_mover() == COMPUTER)
        {
            p2_frogs++;
            board[row][column].make_blank();
        }
        game::make_move(move);
    }

    if (move_type == 0 && !three_in_row())
        game::make_move(move);

    move_type = 0; // default case
    if (!three_in_row())
    { // check if player has all 8 pieces on the board
        if (next_mover() == HUMAN)
        {
            if (p1_tadpoles == 0)
            {
                if (p1_frogs == 0)
                {
                    move_type = 2;
                }
            }
        }
        else if (next_mover() == COMPUTER)
        {
            if (p2_tadpoles == 0)
            {
                if (p2_tadpoles == 0)
                {
                    move_type = 2;
                }
            }
        }
    }
    else // if three in row
        move_type = 1;
}

/**
 * @brief overwrite of the virtual function that can display
 * an example input for the player
 *
 * @return the move the player wishes to make
 */
std::string Boop::get_user_move() const
{
    string answer;

    if (move_type == 0)
    {
        display_message("Your move, please (Ex. TA1): ");
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, answer);
    }
    else if (move_type == 1)
    {
        cout << "You have three pieces in a row! You can remove these pieces to graduate them all to frogs." << endl
             << "Options (Format: Starting tile, direction): " << endl;
        int move_size = move_options.size();
        int j = 1;
        for (int i = 0; i < move_size; i++)
        {
            cout << j << ". ";
            cout << move_options[i] << ", ";
            i++;
            cout << move_options[i] << "; ";
            j++;
        }
        cout << "\nOption number: ";
        if (!isdigit(cin.peek()))
            cin.ignore();
        cin >> j;
        while (j < 1 || j > move_size / 2)
        {
            cout << "Invalid option. Try again: ";
            if (!isdigit(cin.peek()))
                cin.ignore();
            cin >> j;
        }
        j = (j - 1) * 2;
        answer = move_options[j];
        answer += move_options[j + 1];
    }
    else if (move_type == 2)
    {
        cout << "You have eight pieces on the board. You can remove one tadpole to graduate it to a frog," << endl
             << "or remove one frog and return it to your pool." << endl
             << "Enter the address of the piece you wish to graduate (Ex. TA1): ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, answer);
    }
    return answer;
}

/**
 * @brief creates a clone of the board that a computer can use to try out moves
 *
 * @return game board clone
 */
game *Boop::clone() const
{
    Boop *tmp = new Boop();

    // copy the game state
    tmp->p1_frogs = this->p1_frogs;
    tmp->p2_frogs = this->p2_frogs;
    tmp->p1_tadpoles = this->p1_tadpoles;
    tmp->p2_tadpoles = this->p2_tadpoles;
    tmp->move_type = this->move_type;
    tmp->move_options = this->move_options;

    // copy the board state
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            tmp->board[i][j] = this->board[i][j];
        }
    }
    return tmp;
}

/**
 * @brief creates a possible queue of moves that the computer can make
 *
 * @param moves the queue to change
 */
void Boop::compute_moves(queue<string> &moves) const
{
    string tmp = "";
    if (move_type == 0)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j].get_state() == "blank")
                {
                    if (p2_tadpoles > 0)
                    {
                        tmp = tmp + "T" + char(j + 65) + to_string(i + 1);
                        if (is_legal(tmp))
                        {
                            moves.push(tmp);
                        }
                        tmp = "";
                    }
                    if (p2_frogs > 0)
                    {
                        tmp = tmp + "F" + char(j + 65) + to_string(i + 1);
                        if (is_legal(tmp))
                        {
                            moves.push(tmp);
                        }
                        tmp = "";
                    }
                }
            }
        }
    }
    else if (move_type == 1)
    {
        int move_size = move_options.size();
        for (int i = 0; i < move_size; i++)
        {
            tmp += move_options[i];
            i++;
            tmp += move_options[i];
            if (is_legal(tmp))
            {
                moves.push(tmp);
            }
            tmp = "";
        }
    }
    else if (move_type == 2)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j].get_player() == 2)
                {
                    if (board[i][j].get_state() == "tadpole")
                    {
                        tmp = tmp + "T" + char(j + 65) + to_string(i + 1);
                        if (is_legal(tmp))
                        {
                            moves.push(tmp);
                        }
                        tmp = "";
                    }
                    if (board[i][j].get_state() == "frog")
                    {
                        tmp = tmp + "F" + char(j + 65) + to_string(i + 1);
                        if (is_legal(tmp))
                        {
                            moves.push(tmp);
                        }
                        tmp = "";
                    }
                }
            }
        }
    }
}

/**
 * @brief display the status of the current game,
 * including the board and number of pieces per player
 */
void Boop::display_status() const
{
    cout << endl;
    cout << "  |   A.   |   B.   |   C.   |   D.   |   E.   |   F.   |" << endl;
    cout << "--|--------|--------|--------|--------|--------|--------|" << endl;
    for (int i = 0; i < SIZE; i++) // for each row
    {

        for (int k = 0; k < 3; k++) // for each pixel per row
        {

            if (k == 0 || k == 2)
            {
                cout << "  |";
            }
            else if (k == 1)
            {
                cout << i + 1 << ".|";
            }
            for (int j = 0; j < SIZE; j++) // for each column
            {
                if (board[i][j].get_player() == 1)
                {
                    cout << GREEN;
                }
                else if (board[i][j].get_player() == 2)
                {
                    cout << CYAN;
                }
                if (k == 0)
                {
                    cout << board[i][j].get1();
                }
                else if (k == 1)
                {
                    cout << board[i][j].get2();
                }
                else if (k == 2)
                {
                    cout << board[i][j].get3();
                }
                cout << RESET << "|";
            }
            cout << endl;
        }
        cout << "--|--------|--------|--------|--------|--------|--------|" << endl;
    }
    cout << endl;
    cout << GREEN << "PLAYER 1               "
         << CYAN << "PLAYER 2               " << endl;
    cout << RESET << "# of frogs:    " << GREEN << p1_frogs << RESET << "       # of frogs:    " << CYAN << p2_frogs << endl;
    cout << RESET << "# of tadpoles: " << GREEN << p1_tadpoles << RESET << "       # of tadpoles: " << CYAN << p2_tadpoles << endl
         << endl;
    cout << RESET << endl;
}

int Boop::evaluate() const
{
    int ans = 0;
    int next_pt = 5;
    if (move_type == 1 && next_mover() == COMPUTER)
    {
        ans++;
    }
    if (move_type == 1 && next_mover() == HUMAN)
    {
        ans--;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // if players have a piece on the board, give them a point
            // if that piece is a frog give them another

            if (board[i][j].get_player() == 1)
            {
                if (i > 1)
                    ans -= 2;
                if (i < 4)
                    ans -= 2;
                if (j > 1)
                    ans -= 2;
                if (j < 4)
                    ans -= 2;
                ans--;
                if (board[i][j].get_state() == "frog")
                    ans -= 10;
            }
            if (board[i][j].get_player() == 2)
            {
                if (i > 1)
                    ans += 2;
                if (i < 4)
                    ans += 2;
                if (j > 1)
                    ans += 2;
                if (j < 4)
                    ans += 2;
                ans++;
                if (board[i][j].get_state() == "frog")
                    ans += 10;
            }

            // if the player has two or more frogs next to each other, give them a point
            if (board[i][j].get_state() == "frog" && board[i][j].get_player() == 1)
            {
                if (i != 5 && i != 4) // don't walk off the board down
                {
                    if (board[i][j] == board[i + 1][j] && board[i + 1][j].get_state() == "frog") // check vertical
                    {
                        ans -= next_pt;
                        if (board[i][j] == board[i + 2][j] && board[i + 2][j].get_state() == "frog")
                            ans -= 10;
                    }
                    if (j != 5 && j != 4) // don't walk off the board diagonally right
                    {
                        if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1].get_state() == "frog") // check diagonal right
                        {
                            ans -= next_pt;
                            if (board[i][j] == board[i + 2][j + 2] && board[i + 2][j + 2].get_state() == "frog")
                                ans -= 10;
                        }
                    }
                    if (j != 0 && j != 1) // don't walk off the board diagonally left
                    {
                        if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1].get_state() == "frog") // check diagonal left
                        {
                            ans -= next_pt;
                            if (board[i][j] == board[i + 2][j - 2] && board[i + 2][j - 2].get_state() == "frog")
                                ans -= 10;
                        }
                    }
                }
                if (j != 5 && j != 4) // don't walk off the board right
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j + 1].get_state() == "frog") // check horizontal
                    {
                        ans -= next_pt;
                        if (board[i][j] == board[i][j + 2] && board[i][j + 2].get_state() == "frog")
                            ans -= 10;
                    }
                }
            }
            if (board[i][j].get_state() == "frog" && board[i][j].get_player() == 2)
            {
                if (i != 5 && i != 4) // don't walk off the board down
                {
                    if (board[i][j] == board[i + 1][j] && board[i + 1][j].get_state() == "frog") // check vertical
                    {
                        ans += next_pt;
                        if (board[i][j] == board[i + 2][j] && board[i + 2][j].get_state() == "frog")
                            ans += 10;
                    }
                    if (j != 5 && j != 4) // don't walk off the board diagonally right
                    {
                        if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1].get_state() == "frog") // check diagonal right
                        {
                            ans += next_pt;
                            if (board[i][j] == board[i + 2][j + 2] && board[i + 2][j + 2].get_state() == "frog")
                                ans += 10;
                        }
                    }
                    if (j != 0 && j != 1) // don't walk off the board diagonally left
                    {
                        if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1].get_state() == "frog") // check diagonal left
                        {
                            ans += next_pt;
                            if (board[i][j] == board[i + 2][j - 2] && board[i + 2][j - 2].get_state() == "frog")
                                ans += 10;
                        }
                    }
                }
                if (j != 5 && j != 4) // don't walk off the board right
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j + 1].get_state() == "frog") // check horizontal
                    {
                        ans += next_pt;
                        if (board[i][j] == board[i][j + 2] && board[i][j + 2].get_state() == "frog")
                            ans += 10;
                    }
                }
            }
            // if the player has two or more tadpoles next to each other, give them a point
            if (board[i][j].get_state() == "tadpole" && board[i][j].get_player() == 1)
            {
                if (i != 5 && i != 4) // don't walk off the board down
                {
                    if (board[i][j] == board[i + 1][j] && board[i + 1][j].get_state() == "tadpole") // check vertical
                        ans -= (next_pt - 2);
                    if (j != 5 && j != 4) // don't walk off the board diagonally right
                    {
                        if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1].get_state() == "tadpole") // check diagonal right
                            ans -= (next_pt - 2);
                    }
                    if (j != 0 && j != 1) // don't walk off the board diagonally left
                    {
                        if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1].get_state() == "tadpole") // check diagonal left
                            ans -= (next_pt - 2);
                    }
                }
                if (j != 5 && j != 4) // don't walk off the board right
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j + 1].get_state() == "tadpole") // check horizontal
                        ans -= (next_pt - 2);
                }
            }
            if (board[i][j].get_state() == "tadpole" && board[i][j].get_player() == 2)
            {
                if (i != 5 && i != 4) // don't walk off the board down
                {
                    if (board[i][j] == board[i + 1][j] && board[i + 1][j].get_state() == "tadpole") // check vertical
                        ans += (next_pt - 2);
                    if (j != 5 && j != 4) // don't walk off the board diagonally right
                    {
                        if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1].get_state() == "tadpole") // check diagonal right
                            ans += (next_pt - 2);
                    }
                    if (j != 0 && j != 1) // don't walk off the board diagonally left
                    {
                        if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1].get_state() == "tadpole") // check diagonal left
                            ans += (next_pt - 2);
                    }
                }
                if (j != 5 && j != 4) // don't walk off the board right
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j + 1].get_state() == "tadpole") // check horizontal
                        ans += (next_pt - 2);
                }
            }
        }
    }

    ans -= p1_frogs;
    ans += p1_tadpoles;
    ans += p2_frogs;
    ans -= p2_tadpoles;
    return ans;
}

/**
 * @brief determines whether a player has won (three frogs in a row)
 *
 * @return if the game is over
 */
bool Boop::is_game_over() const
{
    for (int p = 1; p <= 2; p++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j].get_state() == "frog" && board[i][j].get_player() == p)
                {
                    if (i != 5 && i != 4) // don't walk off the board down
                    {
                        if (board[i][j] == board[i + 1][j] && board[i + 1][j].get_state() == "frog" && board[i][j] == board[i + 2][j] && board[i + 2][j].get_state() == "frog") // check vertical
                        {
                            return true;
                        }
                        if (j != 5 && j != 4) // don't walk off the board diagonally right
                        {
                            if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1].get_state() == "frog" && board[i][j] == board[i + 2][j + 2] && board[i + 2][j + 2].get_state() == "frog") // check diagonal right
                            {
                                return true;
                            }
                        }
                        if (j != 0 && j != 1) // don't walk off the board diagonally left
                        {
                            if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1].get_state() == "frog" && board[i][j] == board[i + 2][j - 2] && board[i + 2][j - 2].get_state() == "frog") // check diagonal left
                            {
                                return true;
                            }
                        }
                    }
                    if (j != 5 && j != 4) // don't walk off the board right
                    {
                        if (board[i][j] == board[i][j + 1] && board[i][j + 1].get_state() == "frog" && board[i][j] == board[i][j + 2] && board[i][j + 2].get_state() == "frog") // check horizontal
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 * @brief check that the users move string is legal
 *
 * @param move the move string the user wishes to use
 *
 * @return if the move is legal
 */
bool Boop::is_legal(const std::string &move) const
{
    if (move.length() < 3)
        return false;

    if (move_type != 1)
    {
        if (move.length() != 3)
            return false;
    }

    char piece = move[0];
    int column = int(toupper(move[1]) - 'A');
    int row = move[2] - '1';
    int p = 2;

    if ((column < 0 || column > SIZE))
        return false; // check if the column is valid

    if (row < 0 || row > SIZE)
        return false; // check if the row is valid

    if ((piece != 'f' && piece != 'F' && piece != 't' && piece != 'T'))
        return false; // check if the piece type is valid

    if (next_mover() == HUMAN)
        p = 1;

    if (piece == 'f' || piece == 'F')
    {
        if ((next_mover() == HUMAN && p1_frogs > 0) || (next_mover() == COMPUTER && p2_frogs > 0))
        {
            if (board[row][column].get_state() == "blank" && move_type == 0)
                return true;
        }
        if (board[row][column].get_state() != "blank" && board[row][column].get_player() == p && (move_type == 1 || move_type == 2))
            return true;
    }
    else if (piece == 't' || piece == 'T')
    {
        if ((next_mover() == HUMAN && p1_tadpoles > 0) || (next_mover() == COMPUTER && p2_tadpoles > 0))
        {
            if (board[row][column].get_state() == "blank" && move_type == 0)
                return true;
        }
        if (board[row][column].get_state() != "blank" && board[row][column].get_player() == p && (move_type == 1 || move_type == 2))
            return true;
    }

    return false; // default case
}

/**
 * @brief determines whether a player qualifies for a cat graduation (three frogs/tadpoles/mixed in a row),
 * also appends to a vector of move options and directions
 *
 * @return true if there are three in a row in any direction
 */
bool Boop::three_in_row()
{
    move_options.clear();
    bool ans = false;
    string tmp = "";
    int p = 2;
    if (next_mover() == HUMAN)
        p = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j].get_state() != "blank" && board[i][j].get_player() == p)
            {
                if (i != 5 && i != 4) // don't walk off the board (down)
                {
                    if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) // check vertical
                    {
                        tmp = tmp + "T" + char(j + 65) + to_string(i + 1);
                        move_options.push_back(tmp);
                        tmp = "";
                        move_options.push_back("down");
                        ans = true;
                    }
                    if (j != 5 && j != 4) // don't walk off the board diagonally right
                    {
                        if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2]) // check diagonal right
                        {
                            tmp = tmp + "T" + char(j + 65) + to_string(i + 1);
                            move_options.push_back(tmp);
                            tmp = "";
                            move_options.push_back("diagonal right");
                            ans = true;
                        }
                    }
                    if (j != 0 && j != 1) // don't walk off the board diagonally left
                    {
                        if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2]) // check diagonal left
                        {
                            tmp = tmp + "T" + char(j + 65) + to_string(i + 1);
                            move_options.push_back(tmp);
                            tmp = "";
                            move_options.push_back("diagonal left");
                            ans = true;
                        }
                    }
                }
                if (j != 5 && j != 4) // don't walk off the board (right)
                {
                    if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) // check horizontal
                    {
                        tmp = tmp + "T" + char(j + 65) + to_string(i + 1);
                        move_options.push_back(tmp);
                        tmp = "";
                        move_options.push_back("right");
                        ans = true;
                    }
                }
            }
        }
    }
    return ans;
}
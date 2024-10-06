//***********************************************************
//
//  File:     boop.h
//
//  Author:   Karli Nadsady
//  Email:    kn274621@ohio.edu
//
//  Description: The Boop class contains functions for playing
//               the Boop game. It holds the # of game pieces
//               for each player as well as the various moves
//               each player can make.
//
//***********************************************************

#ifndef BOOP_H
#define BOOP_H

#include "game.h"
#include "spaces.h"

using namespace main_savitch_14;

class Boop : public main_savitch_14::game
{
public:
    Boop();

    // overwritten virtual functions
    void restart();
    void make_move(const std::string &move);
    std::string get_user_move() const;

    // purely virtual functions from game class
    game *clone() const;
    void compute_moves(std::queue<std::string> &moves) const;
    void display_status() const;
    int evaluate() const;
    bool is_game_over() const;
    bool is_legal(const std::string &move) const;

private:
    static const int SIZE = 6;
    Spaces board[SIZE][SIZE];
    int p1_frogs;
    int p2_frogs;
    int p1_tadpoles;
    int p2_tadpoles;
    int move_type; // 0 is default, 1 is graduate three pieces to frogs, 2 is graduate 8 tadpoles to frogs
    std::vector<std::string> move_options;

    // my functions
    bool three_in_row();
};

#endif
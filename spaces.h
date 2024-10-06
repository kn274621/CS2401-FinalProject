//***********************************************************
//
//  File:     spaces.h
//
//  Author:   Karli Nadsady
//  Email:    kn274621@ohio.edu
//
//  Description: The class Spaces houses data for each game
//               space in the game Boop. It can set the state
//               of each space (frog, tadpole, blank).
//
//***********************************************************
#ifndef SPACES_H
#define SPACES_H

#include <string>

class Spaces
{
public:
    Spaces();
    void make_blank();
    void make_tadpole(int p);
    void make_frog(int p);
    int get_player() const { return player; }
    std::string get_state() const { return state; }
    std::string get1() const { return row1; }
    std::string get2() const { return row2; }
    std::string get3() const { return row3; }

    bool operator==(const Spaces other) const;
    Spaces& operator=(const Spaces& other);

private:
    int player;        // player 1 or player 2 (0 for blank)
    std::string state; // blank, frog, or tadpole
    std::string row1;  // 8 by 3
    std::string row2;  // 8 by 3
    std::string row3;  // 8 by 3

    // frog
    //      O..O
    //     (----)
    //    ( >__< )
    //    12345678

    // tadpole
    //   o~~~
    // 12345678
};

#endif
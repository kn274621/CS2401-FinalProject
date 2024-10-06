#include "spaces.h"
#include <iostream>
#include "colors.h"

using namespace std;

/**
 * @brief initializes a blank space with length of 8
 * and height of 3
 */
Spaces::Spaces()
{
    state = "blank";
    row1 = "        ";
    row2 = "        ";
    row3 = "        ";
    player = 0;
}

/**
 * @brief change the state of a space to blank
 */
void Spaces::make_blank()
{
    state = "blank";
    row1 = "        ";
    row2 = "        ";
    row3 = "        ";
    player = 0;
}

/**
 * @brief change the state of a space to a tadpole
 */
void Spaces::make_tadpole(int p)
{
    state = "tadpole";
    row1 = "        ";
    row2 = "  o~~~  ";
    row3 = "        ";
    player = p;
}

/**
 * @brief change the state of a space to a frog
 */
void Spaces::make_frog(int p)
{
    state = "frog";
    row1 = "  O..O  ";
    row2 = " (----) ";
    row3 = "( >__< )";
    player = p;
}

bool Spaces::operator==(const Spaces other) const
{
    if (player == other.player && state != "blank" && other.state != "blank")
    {
        return true;
    }
    return false; // base case
}
Spaces& Spaces::operator=(const Spaces& other)
{
    if (this != &other) // self-assignment check
    {
        this->state = other.state;
        this->row1 = other.row1;
        this->row2 = other.row2;
        this->row3 = other.row3;
        this->player = other.player;
    }
    return *this;
}
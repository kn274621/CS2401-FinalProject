/*************************************************************************
   This is a sample of what the main should like for the final phase of 
   the Boop game.

   Patricia Lindner	Ohio University		Fall 2023
*************************************************************************/
#include <iostream>
#include "boop.h"

using namespace std;
using namespace main_savitch_14;


int main(){
   Boop mygame;
   game::who winner = mygame.play();

   if(winner == game::HUMAN) cout << "Player 1 Wins!\n\n";
   else cout << "Player 2 Wins!\n\n";

   return 0;
}
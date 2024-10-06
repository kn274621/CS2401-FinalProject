
CS 2401 – Fall 2023
# Project 6 – Boop

The final project for CS 2401 is a single large project to be submitted in three stages counting as three projects. For this project we will be implementing the game Boop, with the final product being a program that can play an "intelligent" game of Boop against a human opponent.  

This game must be derived from the files I have given you (a game class written by the author of a textbook we used to use for this course). The files are game.h and game.cc. I have also included a file called colors.h which was created by a former student who has given us permission to use it. It allows you to adjust the colors of the terminal screen during a text-based console or ssh session. I have altered the play function in the game class slightly by adding three different sections of code that you will need for each part of this project. **Make sure that you are using the correct version of the play function for each part or the program will not work correctly.**  

The game class creates a map for us in how the project is developed, and at the end we will find that most of the “AI” has already been written for us in this parent class. If you look at game.h, you will see that there are virtual functions that must be overridden and some that may optionally be overridden. Eventually you will write a child version for all the mandatory overrides, but you probably do not need to override many of the optional ones.  

The rules of this game are fully outlined in the Boop_Rules.pdf document included with the assignment. Basically, the game consists of two players that each start with 8 “kitten” pieces. You can upgrade “kitten” pieces to “cat” pieces with the goal of the game being to get three “cat” pieces in a row (horizontal, vertical, or diagonal). The catch is that whenever a piece is added to the board, other pieces may need to move. When placing a “kitten” piece, any adjacent kitten pieces get “booped” one space away from the newly placed piece if there is an empty spot in that direction. When placing a “cat” piece, all adjacent cats and kittens get booped.  

***  
 
The first stage is the design stage. In this part you decide how you will represent the pieces and how you will display the board. Good grades are given for the quality of the design, the attractiveness of the board, and the ease of the user interface. Your project should be derived from the game class. You will create a child class called Boop, which needs to have a way of storing the board. The board should be a 6x6 two-dimensional array of spaces where the spaces are another class which you must write (I would suggest using a static const for the size of the board so that you can use it later when checking boundaries). This board becomes the principle private member of the Boop class. The Boop class will also need counters for how many cat and kitten pieces each player has available to them. The spaces class should be able to store all the attributes that a space might have – emptiness, color/owner, piece type, as well as mutator and accessor functions to transform a piece/space from one state to another. At any point, you can add any additional attributes or functions to the Boop class that you find to be useful.  

You must design your own characters. I suggest using a single line character and a 3 line character, but you can do whatever you like. You may not use the same characters from my example game. Your junior character (the kitten equivalent) needs to be distinctly different so that they are easy to tell apart when they are on the board together.  

You should then implement your design to the stage where I can see the board displayed and be allowed to make one initial move.  
The first step in doing this is to write your space class, which will be a standalone class (not derived from anything). You can choose to represent the state of the space in many ways, so this design decision is left up to you.  
Then, when you write your Boop class, which will be derived from the game class, the best first step, after declaring your board, is to create stubs for all the game class’s purely virtual functions. (A stub is a function with an empty implementation, which exists merely to validate a call, or to allow the program to compile.) For this stage you must write a real implementation for restart, display_status and a very simplified make_move, and is_legal. These functions should do the following:  
* restart: set the initial piece counters to the correct number (8 junior pieces for each player and 0 senior pieces for each player), set the status of every space on the board to empty, and call the game::restart() function to reset the move counter.  
* display_status: show the current state of the board. You will need to use nested loops for this to walk through each row column by column and output some representation of what piece on on that space.  
* make_move: set the status of the space at the row and column given by the move string to whatever type of piece and player that made the move. You should also call game::make_move(move) to increment the turn counter.  
* is_legal: make sure the move string has the correct format, that it would be ok to put a piece on the space requested (the space must currently be empty), and that the player whose turn it is has enough of the type of piece requested.  

Notice that the move is to be entered and passed around as a string, and you need to stay with this as it is an essential part of the design. Think of the string as merely a container for characters. You can determine the format of this string but be sure that the user is aware of the format you are expecting (putting a note in the restart function is a good way to do this).  
 
**Submission of this 50-point stage (6a) is due at 11:59 p.m. on Wednesday November 22nd.**

***  
 
In the second stage you must implement a fully functional two-player game which allows two humans to play the game against each other. (You will have one of the humans "be" the computer in the terms of the game class.) All rules should now be enforced. This is the hardest stage of this project so you will want to start on this as soon as possible. This stage will involve:  
* Overriding the get_user_move function to account for the three different move types (this is not strictly required, but very helpful).  
* A much more extensive make_move function. You will need to be able to:  
  * Put the new piece that was requested onto the board  
  * Check for a group of three that should be removed and graduated to cats  
  * Check for all 8 of the player’s pieces being on the board in which case, they can remove one and get a cat added to their pool.  
  * To successfully complete the final stage of this project, I suggest that you design your code to work in this way (you will have to use this system eventually, so might as well design this way from the start):  
      * The “top” level Boop::make_move should check a private variable that indicates which of the three types of moves the user should be making.  
      * If the turn type is a new move, call a function to:  
        * Put that piece on the board  
        * Boop all neessary adjacent pieces  
        * Check for groups of three  
          * If you find any, set the turn type to your “removing three” indicator and return WITHOUT calling game::make_move  
        * Check for all 8 pieces being on the board  
          * If this is true, set the turn type to your “removing one” indicator and return WITHOUT calling game::make_move  
        * If you do not detect either of the secondary types of moves, call game::make_move to switch to the next player’s turn.  
      * If the turn type is removing three  
        * Remove the three pieces from the board and add three cats to the player’s pool  
        * Call game::make_move to switch to the next player’s turn  
      * If the turn type is removing one  
        * Remove that piece and add one cat to the player’s pool  
        * Call game::make_move to switch to the next player’s turn  
* A more extensive is_legal function (if you implemented the suggested make_move system). You will need to be able to handle verifying each of the 3 different types of moves. I would suggest structuring your Boop::is_legal to check the turn type and then call a function to do the input verification for each of the different move formats that you have chosen.  
* Writing is_game_over which should check for three cat pieces in a row of either color.  
* Writing evaluate which should return a negative number if player 1 (HUMAN) is winning and a positive number if player 2 (COMPUTER) is winning.

**NOTE:** You do NOT want to call display_status inside the make_move or is_legal functions or you will make the program very difficult to debug in the next stage.

**Submission of this 50-point stage (6b) is due at 11:59 p.m. on Wednesday December 6th.**

***  

In the final stage the computer will play an "intelligent" game against a human opponent. Again, all rules should be enforced, and the computer should not cheat. This is the "AI" stage of the game, and you will find that most of the AI work is done already by the game class. You may find during this stage that the computer makes moves that should not be allowed, in which case you will need to fix your is_legal and possibly make_move functions. The other functions you need to implement for the computer to be able to play are:  
* compute_moves: this function takes a queue as an argument that you must fill with all the legal moves the computer could make given the current status of the board. For the “modular” design proposed above, this means that you will need three different sections to your compute_moves function that take into account what type of move the computer is trying to make. This function should:  
  * Construct a correctly formatted move string for the type of move the computer should be making  
  * Pass it to is_legal  
  * If it is legal, push it into the moves queue (the functions parameter is a queue passed by reference)  
* clone: create a copy of the board. You can do this using the default copy constructor:  
  * return new Boop(*this);  
* You should probably revisit your evaluate. The computer will use the return value of this function to pick moves, so you need to give different "weights" to different board situations. Keep in mind that positive numbers returned from this function are good for the computer.  
  * Examples of things to consider:  
    * Number of kittens/cats each player has placed on the board  
    * Number of kittens/cats in each player’s pool  
    * 2 or 3 kittens/cats of the same color next to each other on the board  
  * You will likely need to do a lot of trial and error to find good weights that make the computer play intelligently. You can also try tuning the SEARCH_LEVELS parameter in game.h  
* I found that for the computer to play intelligently, it was very important to teach it NOT to remove 3 cats in a row (of either player's) and then continue playing. To do this:  
  * I implemented a "hidden" move string. The main place that this comes into play is in compute_moves. Before you start constructing move strings, check to make sure there are not 3 cats in a row somewhere. If there are, however, you don't want the computer to do anything because the game is done. So, instead of pushing legal moves into the queue, push a distinct string that indicates that no one should make any more moves.  
  * In is_legal, if the move that you are checking is equal to your game over string:  
    * Check to see if there are 3 in a row, if so, return true, if not, return false. This check is necessary so that someone does not find this hidden string and use it to skip turns when they shouldn't be allowed to.  
  * In make_move, if the move that you are checking is equal to your game over string, then just switch players by calling game::make_move and return.
    
**Submission of this 50-point stage (6c) is due on Wednesday December 13th at 10:10 a.m.**

// File: game.h (part of the namespace main_savitch_14)
// This code comes from an old textbook used for CS 2401 at Ohio University
// This class can be used as a basis to create any game


#ifndef MAIN_SAVITCH_GAME
#define MAIN_SAVITCH_GAME
#include <queue>   // Provides queue<string>
#include <string>  // Provides string

namespace main_savitch_14
{
    class game
    {
		public:
			// ENUM TYPE
			enum who { HUMAN, NEUTRAL, COMPUTER }; // Possible game outcomes
			
			// CONSTRUCTOR and DESTRUCTOR
			game( ) { move_number = 0; }
			virtual ~game( ) { }
			
			// PUBLIC MEMBER FUNCTIONS
			// The play function should not be overridden. It plays one game,
			// with the human player moving first and the computer second.
			// The computer uses an alpha-beta look ahead algorithm to select its
			// moves. The return value is the winner of the game (or NEUTRAL for
			// a tie).
			who play( );

		protected:
			// *******************************************************************
			// OPTIONAL VIRTUAL FUNCTIONS (overriding these is optional)
			// *******************************************************************
			virtual void display_message(const std::string& message) const;
			
			/* 
			although the get_user_move function is listed as an optional override, 
			you may want to override it to consider the type of move since 
			you will have 3 distince move formats.
			*/
			virtual std::string get_user_move( ) const;
			
			virtual who last_mover( ) const 
				{ return (move_number % 2 == 1 ? HUMAN : COMPUTER); }
			
			virtual int moves_completed( ) const { return move_number; }
			
			virtual who next_mover( ) const
				{ return (move_number % 2 == 0 ? HUMAN : COMPUTER); }
			
			virtual who opposite(who player) const
				{ return (player == HUMAN) ? COMPUTER : HUMAN; }
			
			/* 
			although the winning function is listed as an optional override, 
			you should write your own evaluate() for winning() to work properly.
			evaluate should return a negative number if player 1 is winning and
			a positive number if player 2 is winning.
			*/
			virtual who winning( ) const;

			// *******************************************************************
			// VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEN:
			// The overriding function should call the original when it finishes.
			// *******************************************************************
			// Have the next player make a specified move:
			virtual void make_move(const std::string& move) { ++move_number; }

			// Restart the game from the beginning:
			virtual void restart( ) { move_number = 0; }

			// *******************************************************************
			// PURE VIRTUAL FUNCTIONS
			// *******************************************************************
			// (these must be provided for each derived class)
			// Return a pointer to a copy of myself:
			virtual game* clone( ) const = 0;

			// Compute all the moves that the next player can make:
			virtual void compute_moves(std::queue<std::string>& moves) const = 0;

			// Display the status of the current game:
			virtual void display_status( ) const = 0;

			// Evaluate a board status
			// NOTE: positive values are good for the computer.
			virtual int evaluate( ) const = 0;

			// Return true if the current game is finished:
			virtual bool is_game_over( ) const = 0;

			// Return true if the given move is legal for the next player:
			virtual bool is_legal(const std::string& move) const = 0;

		private:
			// MEMBER VARIABLES
			int move_number;	// Number of moves made so far

			// STATIC MEMBER CONSTANT
			/* Levels for look-ahead evaluation.
			You can change this number if you would like to to try to adjust the difficulty.
				If you want me to use a different number when testing, please note that
				in your submission text.
			*/
			static const int SEARCH_LEVELS = 2;
		
			// PRIVATE FUNCTIONS (these are the same for every game)
			int eval_with_lookahead(int look_ahead, int beat_this);
			void make_computer_move( );
			void make_human_move( );
	};
}

#endif
#ifndef PLAYERIA_HPP
#define PLAYERIA_HPP

#define nbProcess 3
#define nbThread 3
#define DEPTH 8

#include "connectFour.hpp"

class result
{
public:
	typePiece winner;
	int turnToTheEnd;
	result()
	{
		winner = NONE;
		turnToTheEnd = 0;
	}
	
	int compare2(result &other, typePiece currentPlayer)
	{
		if (winner == BEGIN)
			return (1);
		if (winner == NONE)
		{
			if (currentPlayer == other.winner)
				return (1);
			if (other.winner == NONE && other.turnToTheEnd > turnToTheEnd)
				return (1);
			return (0);
		}
		if (currentPlayer == other.winner)
		{
			if (other.winner == currentPlayer && other.turnToTheEnd < turnToTheEnd)
				return (1);
			return(0);
		}
		if (other.winner != winner)
			return (1);
		if (other.winner == winner && other.turnToTheEnd > turnToTheEnd)
			return (1);
		return (0);
	}

	bool compare(result &other, typePiece currentPlayer)
	{
		int a = compare2(other, currentPlayer);
		if (a > 0)
		{ 
			winner = other.winner;
			turnToTheEnd = other.turnToTheEnd;
			return (true);
		}
		return (false);
	}
};

class simulation : public referee, public result
{
public:
	typePiece currentPlayer;
	int x;
	int depth;
	std::vector<simulation> nextSimulation;
	void createNewBranch2(int depthMax, boardGame &board);
	void createNewBranch(int depthMax, boardGame &board);
	bool referee(boardGame &board);
	simulation(typePiece _currentPlayer, int _depth, int _x);
	int getFinalMoove()
	{
		std::cout << winner << " " << turnToTheEnd << std::endl;
		std::cout << nextSimulation.size() << std::endl;
		for (std::vector<simulation>::iterator it=nextSimulation.begin(); it != nextSimulation.end(); ++it)
		{
			std::cout << it->winner << " " << it->turnToTheEnd << " " << it->x << std::endl;
			if (winner == it->winner && turnToTheEnd == it->winner)
				return (it->x);
		}
		return (nextSimulation.back().x);
	}

	void removeVector()
	{
		for (unsigned int _x = 0; _x < nextSimulation.size(); _x++)
		{
			nextSimulation.erase(nextSimulation.begin() + _x);
			_x--;
		}
	}
};

class Process : public boardGame
{
public:
	Process(boardGame &_board)
	{
		currentPlayer = _board.currentPlayer;
		columns = _board.columns;
		axis = _board.axis;
		for (int y = 0; y < 6; y++)
			for (int x = 0; x < 7; x++)
				board[y][x] = _board.board[y][x];
		for (int _x = 0; _x < 7; _x++)
			columns[_x] = _board.columns[_x];
	}
	void play(simulation &sim)
	{
		int depth = 0;
		while (depth < DEPTH && sim.winner == NONE)
		{
			sim.createNewBranch(depth, *this);
			depth++;
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
		}
	}
};

class playerIa : public player
{
public:
	playerIa()
	{
		waitEvent = false;
	}
	bool play(game &engine)
	{
		simulation *sim = new simulation(color, -1, -1);
		Process *ia = new Process(engine);
		std::cout << "start" << std::endl;
		ia->play(*sim);
		engine.putPiece(sim->getFinalMoove(), color);
		sim->removeVector();
		std::cout << "end" << std::endl;
		return (true);
	}
};

#endif
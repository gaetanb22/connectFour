#include "playerIa.hpp"

bool simulation::referee(boardGame &board)
{
	board.board[board.columns[x]][x] = currentPlayer;
	board.axis = axisxy(x, board.columns[x]);
	if (refereeing(board, axisxy(x, board.columns[x])) == true)
	{
		turnToTheEnd = depth;
		winner = currentPlayer;
		turnToTheEnd = depth;
		board.board[board.columns[x]][x] = NONE;
		return (true);
	}
	board.board[board.columns[x]][x] = NONE;
	return (false);
}

void simulation::createNewBranch2(int depthMax, boardGame &board)
{
	if (depth == depthMax)
	{
		for (int i = 0; i < 7; i++)
		{
			if (board.columns[i] != 6)
			{
				nextSimulation.push_back(simulation(currentPlayer, depth, i));
				if (nextSimulation.back().referee(board))
				{
					winner = nextSimulation.back().winner;
					turnToTheEnd = nextSimulation.back().turnToTheEnd;
					return;
				}
			}
		}
	}
	else
	{
		winner = BEGIN;
		for (std::vector<simulation>::iterator it=nextSimulation.begin(); it != nextSimulation.end(); ++it)
			if (it->winner == NONE)
			{
				it->createNewBranch(depthMax, board);
				compare(*it, it->currentPlayer);
				if (it->winner == it->currentPlayer)
					return;
			}
		for (unsigned int _x = 0; _x < nextSimulation.size(); _x++)
			if (winner != nextSimulation[_x].winner || turnToTheEnd != nextSimulation[_x].turnToTheEnd)
			{
				nextSimulation.erase(nextSimulation.begin() + _x);
				_x--;
			}
	}
	return;
}

void simulation::createNewBranch(int depthMax, boardGame &board)
{
	if (x != -1)
	{
		board.board[board.columns[x]][x] = currentPlayer;
		board.columns[x]++;
	}
	createNewBranch2(depthMax, board);
	if (x != -1)
	{
		board.columns[x]--;
		board.board[board.columns[x]][x] = NONE;
	}
}

simulation::simulation(typePiece _currentPlayer, int _depth, int _x)
{
	currentPlayer = ((_currentPlayer == RED) ? YELLOW : RED);
	x = _x;
	depth = _depth + 1;
	turnToTheEnd = depth;
	winner = NONE;
}
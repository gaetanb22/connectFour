#include "connectFour.hpp"
#include "playerIa.hpp"

bool limit(int y, int x)
{
	if (y < 6 && y >= 0 && x >= 0 && x < 7)
		return (false);
	return (true);
}

bool referee::getAxis(boardGame &board, axisxy axis, int y, int x, typePiece color)
{
	while (!limit(axis.y, axis.x) && board.board[axis.y][axis.x] == color)
	{
		axis.y -= y;
		axis.x -= x;
	}
	axis.y += y;
	axis.x += x;
	int i = 0;
	while (!limit(axis.y + y * i, axis.x + x * i) && board.board[axis.y + y * i][axis.x + x * i] == color)
	{
		if (i == 4)
			return(true);
		i++;
	}
	if (i == 4)
		return(true);
	return (false);
}

bool referee::refereeing(boardGame &board, axisxy axis)
{
	typePiece color = (typePiece)board.board[axis.y][axis.x];
	//std::cout << axis.y << " " << axis.x << std::endl;
	if (getAxis(board, axis, 0, 1, color))
		return (true);
	if (getAxis(board, axis, 1, 0, color))
		return (true);
	if (getAxis(board, axis, -1, 1, color))
		return (true);
	if (getAxis(board, axis, 1, 1, color))
		return (true);
	return (false);
}

void game::play()
{
	display(*this);
	while (1)
	{
		if (players[currentPlayer]->waitEvent)
			window.waitEvent(event);
		if (players[currentPlayer]->play(*this))
		{
			std::cout << "end3" << std::endl;
			display(*this);
			if (refereeing(*this, axis))
				exit(1);
			std::cout << "end4" << std::endl;
			currentPlayer = (currentPlayer == RED) ? YELLOW : RED;
		}
	}
}

bool humanPlayer::play(game &engine)
{
	sf::Vector2i mouse = engine.getMouse();
	if (engine.mouseReleased() && mouse.x > 0 && mouse.x < 700 && mouse.y > 0 && mouse.y < 600)
		return (engine.putPiece(mouse.x / 100, color));
	return (false);
}

int main()
{
	game connectFour(new humanPlayer(), new playerIa());
	connectFour.play();
}
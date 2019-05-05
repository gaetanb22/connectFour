#ifndef CONNECTFOUR_HPP
#define CONNECTFOUR_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>

class axisxy
{
public:
	int x;
	int y;
	void xy(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	axisxy(int _x, int _y)
	{
		xy(_x, _y);
	}
	axisxy() {}
};

enum typePiece
{
	RED,
	YELLOW,
	NONE,
	BEGIN
};

class boardGame
{
public:
	typePiece currentPlayer; //utile?
	std::array<int, 7>		columns;
	std::array<std::array<int, 7>, 6> board;
	axisxy axis;
	boardGame()
	{
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				board[y][x] = NONE;
			}
		}
		for (int i = 0; i < 7; i++)
		{
			columns[i] = 0;
		}
	}
	bool putPiece(int x, typePiece color)
	{
		if (columns[x] < 6)
		{
			board[columns[x]][x] = color;
			axis.xy(x, columns[x]);
			columns[x]++;
			return (true);
		}
		return (false);
	}
	void show()
	{
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				std::cout << board[y][x];
			}
			std::cout << std::endl;
		}
	}
};

class game;

class player
{
public:
	bool waitEvent;
	typePiece color;
	virtual bool play(game &engine) = 0;
};

class humanPlayer : public player
{
public:
	humanPlayer()
	{
		waitEvent = true;
	}
	bool play(game &engine);
};

class graphic
{
public:
	sf::RenderWindow	window;
	sf::Texture			redT;
	sf::Texture			yellowT;
	sf::Texture			gridT;
	sf::Sprite			red;
	sf::Sprite			yellow;
	sf::Sprite			grid;
	sf::Event			event;
	graphic()
	{
		window.create(sf::VideoMode(700,700), "myWindow", sf::Style::Close);
  		redT.loadFromFile("pictures/red.png");
  		yellowT.loadFromFile("pictures/yellow.png");
  		gridT.loadFromFile("pictures/board.png");
	    red.setTexture(redT);
	    yellow.setTexture(yellowT);
	    grid.setTexture(gridT);
	    grid.setPosition(0, 0);
	}
	sf::Vector2i getMouse()
	{
		return (sf::Mouse::getPosition(window));
	}
	bool mouseReleased()
	{
		if (event.type == sf::Event::MouseButtonReleased)
			return (true);
		return (false);
	}
	void display(boardGame &board)
	{
		int y;
		int x;
		window.clear(sf::Color::Black);
		for (y = 0; y < 6; y++)
		{
			for (x = 0; x < 7; x++)
			{
				if (board.board[y][x] == RED)
				{
					red.setPosition(x * 100, (5 - y) * 100);
					window.draw(red);
				}
				else if (board.board[y][x] == YELLOW)
				{
					yellow.setPosition(x * 100, (5 -y) * 100);
					window.draw(yellow);
				}
			}
		}
		board.show();
		window.draw(grid);
		window.display();
	}
};

class referee
{
public:
	bool getAxis(boardGame &board, axisxy axis, int y, int x, typePiece color);
	bool refereeing(boardGame &board, axisxy axis);
};

class game : public boardGame, public graphic, public referee
{
private:
	std::array<player*, 2> players;
public:
	void play();
	game(player *playerRed, player *playerYellow) : boardGame(), graphic()
	{
		currentPlayer = RED;
		playerRed->color = RED;
		playerYellow->color = YELLOW;
		players[0] = playerRed;
		players[1] = playerYellow;
	}
};

#endif
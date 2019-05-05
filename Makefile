##
## Makefile for Makefile in /home/briand_p/Documents/IA/SOUTENANCE/B5Gomoku/FINAL
##
## Made by Briand
## Login   <briand_p@epitech.net>
##
## Started on  Wed Nov  2 00:33:01 2016 Briand
## Last update Wed Nov  2 00:46:18 2016 Briand
##

CXX	=	c++

RM	=	rm -f

SRCDIR	=	./srcs/

SRC	=	$(SRCDIR)/connectFour.cpp \
		$(SRCDIR)/playerIa.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	connectFour

CXX_FLAGS	+=	-W -Wall -Wextra
CXX_FLAGS	+=	-I./include/SFML
CXX_FLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-system
CXX_FLAGS	+=	-I./include
CXX_FLAGS	+=	-std=c++11


all:		$(NAME)

$(NAME):
		$(CXX) -o $(NAME) $(SRC) $(CXX_FLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

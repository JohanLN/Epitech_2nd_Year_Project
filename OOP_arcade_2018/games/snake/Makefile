##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## compile dynamic lib of the snake game
##

CXXFLAGS	+=	-I ./include -I ../../include/ -I ../../include/interfaces  -W -Wall -Wextra -fPIC

LDFLAGS		+=	-shared

SRC_DIR		=	src/

SRC		=	$(SRC_DIR)Snake.cpp \
			$(SRC_DIR)BodySnake.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME		=	lib_arcade_nibbler.so

all:		$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(LDFLAGS) $(OBJ)
		mv $(NAME) ../

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re

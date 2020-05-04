##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## compile dynamic lib of the snake game
##

CXXFLAGS	+=	-I ./include -I ../../include/ -W -Wall -Wextra -fPIC

LDFLAGS		+=	-shared

SRC_DIR		=	src/

SRC		=	$(SRC_DIR)lib_arcade_sdl.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME		=	lib_arcade_sdl2.so

all:		$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(LDFLAGS) $(OBJ) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -g3
		mv $(NAME) ../

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re

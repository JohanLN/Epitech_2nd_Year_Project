##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## compile dynamic lib of the snake game
##

CXXFLAGS	+=	-I ./include -I ../../include/ -W -Wall -Wextra -fPIC

LDFLAGS		+=	-shared

SRC_DIR		=	src/

SRC		=	$(SRC_DIR)lib_arcade_allegro.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME		=	lib_arcade_allegro.so

all:		$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(LDFLAGS) $(OBJ) -lallegro -lallegro_main -lallegro_dialog -lallegro_font -lallegro_ttf -lallegro_image -g3
		mv $(NAME) ../

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re

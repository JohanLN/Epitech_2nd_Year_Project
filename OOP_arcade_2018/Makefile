##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## compile arcade program
##

CXXFLAGS	+=	-I ./include -I ./include/interfaces -W -Wall -Wextra -g3

LDFLAGS		+= 	-g3

SRC_DIR		=	./src/

GAME_DIR	=	./games/

LIB_DIR		=	./libs/

SRC		=	$(SRC_DIR)main.cpp	\
			$(SRC_DIR)Core.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME		=	arcade

all:		$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(LDFLAGS) $(OBJ) -ldl -g3
		make -C $(GAME_DIR)pacman/
		make -C $(GAME_DIR)snake/
		make -C $(GAME_DIR)solar_fox/
		#make -C $(LIB_DIR)allegro/
		make -C $(LIB_DIR)ncurses/
		make -C $(LIB_DIR)sdl/
		make -C $(LIB_DIR)sfml/

core:		$(OBJ)
		g++ -o $(NAME) $(LDFLAGS) $(OBJ) -ldl

games:
		make -C $(GAME_DIR)pacman/
		make -C $(GAME_DIR)snake/
		make -C $(GAME_DIR)solar_fox/

graphicals:
		make -C $(LIB_DIR)SFML/
		make -C $(LIB_DIR)ncurses/
		#make -C $(LIB_DIR)allegro/
		make -C $(LIB_DIR)sdl/
		make -C $(LIB_DIR)sfml/

clean:
		rm -rf $(OBJ)
		make clean -C $(GAME_DIR)pacman/
		make clean -C $(GAME_DIR)snake/
		make clean -C $(GAME_DIR)solar_fox/
		#make clean -C $(LIB_DIR)allegro/
		make clean -C $(LIB_DIR)ncurses/
		make clean -C $(LIB_DIR)sdl/
		make clean -C $(LIB_DIR)sfml/

fclean:		clean
		rm -rf $(NAME)
		make fclean -C $(GAME_DIR)pacman/
		make fclean -C $(GAME_DIR)snake/
		make fclean -C $(GAME_DIR)solar_fox/
		#make fclean -C $(LIB_DIR)allegro/
		make fclean -C $(LIB_DIR)ncurses/
		make fclean -C $(LIB_DIR)sdl/
		make fclean -C $(LIB_DIR)sfml/


re:		fclean all

.PHONY:		all clean fclean re games

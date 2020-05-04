##
## EPITECH PROJECT, 2018
## Makefile my_malloc
## File description:
## compile the dynamic library libmy_malloc.so and also the test file
##

CFLAGS		+=	-I ./include -W -Wall -Wextra -fPIC -g3

LDFLAGS		+=	-lpthread -L ./ -ldl

SRC_D_OBJ	=	src/objdump/

SRC_D_NM	=	src/nm/

SRC_OBJ         =	$(SRC_D_OBJ)my_objdump.c	\
			$(SRC_D_OBJ)data.c		\
			$(SRC_D_OBJ)header.c		\
			$(SRC_D_OBJ)parser.c


SRC_NM         =	$(SRC_D_NM)my_nm.c		\
			$(SRC_D_NM)parser.c		\
			$(SRC_D_NM)symbol.c		\
			$(SRC_D_NM)data.c

OBJ_OBJ		    =	$(SRC_OBJ:.c=.o)

OBJ_NM		    =	$(SRC_NM:.c=.o)

NAME_OBJ	=	my_objdump

NAME_NM		=	my_nm

all:		$(NAME_OBJ) $(NAME_NM)

$(NAME_OBJ):	$(OBJ_OBJ)
		gcc -o $(NAME_OBJ) $(LDFLAGS) $(OBJ_OBJ)

$(NAME_NM):	$(OBJ_NM)
		gcc -o $(NAME_NM) $(LDFLAGS) $(OBJ_NM)

objdump:	$(OBJ_OBJ)
		gcc -o $(NAME_OBJ) $(LDFLAGS) $(OBJ_OBJ)

nm:		$(OBJ_NM)
		gcc -o $(NAME_NM) $(LDFLAGS) $(OBJ_NM)

clean:
		rm -rf $(OBJ_OBJ)
		rm -rf $(OBJ_NM)

fclean:		clean
		rm -rf $(NAME_OBJ)
		rm -rf $(NAME_NM)

re:		fclean all

.PHONY:		all clean fclean re

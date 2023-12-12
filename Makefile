NAME = pipex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MSRC = pipex.c utils.c parsing.c parsincv2.c 

MOBJ = ${MSRC:.c=.o}

all : $(NAME)

$(NAME) : $(MOBJ) pipex.h
	@ar rc $(NAME) $(MOBJ)
	@${CC} ${CFLAGS} pipex.c ${NAME} -o pipex
clean :
	@${RM} ${MOBJ}
fclean : clean
	@${RM} $(NAME) pipex
re : fclean all
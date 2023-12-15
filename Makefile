NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MSRC = pipex.c utils.c utilsv2.c parsing.c parsingv2.c 

MOBJ = $(MSRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC)	$(CFLAGS) -c $< -o $@

$(NAME): $(MOBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(MOBJ)

clean:
	$(RM) $(MOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

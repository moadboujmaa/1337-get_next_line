SRC = get_next_line.c get_next_line_utils.c
BSRC = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
NAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(BOBJ)
	ar rcs $(NAME) $(BOBJ)

%.o: %.c get_next_line.h get_next_line_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
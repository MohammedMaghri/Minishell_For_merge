SRC = parcing/better_split.c parcing/check_validity.c parcing/parcing.c parcing/skip_empty_blocks.c \
	parcing/check_validity_2.c utils/exits.c utils/libft_functions/libft_functions_1.c \
	utils/libft_functions/libft_functions_2.c utils/libft_functions/libft_functions_3.c \
 	utils/list_center.c utils/gc.c utils/tree.c utils/gnl.c main.c

OBJ = $(SRC:.c=.o)

CFALG = -Wall -Wextra -Werror -g

LINKING = -lreadline

NAME = minishell


all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(CFALG) $(LINKING) -fsanitize=address -o $@

%.o:%.c minishell.h
	cc $(CFALG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
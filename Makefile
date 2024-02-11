SRC = parcing/better_split.c parcing/parcing.c utils/libft_functions.c utils/libft_functions_2.c parcing/skip_empty_blocks.c utils/list_center.c execution/cd.c execution/cd_function_utils.c utils/gc.c execution/all_basic_functions.c execution/cd_utils.c execution/exit.c  execution/export_function.c execution/export_function_utils.c execution/pwd_show.c execution/pwd_path.c  execution/list_with_execve.c execution/echo.c main.c 

OBJ = $(SRC:.c=.o)

CFALG = -Wall -Wextra -Werror

LINKING = -lreadline

NAME = minishell


all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(CFALG) $(LINKING) -o $@

%.o:%.c minishell.h
	cc $(CFALG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean

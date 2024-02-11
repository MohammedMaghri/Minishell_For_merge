/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:21:05 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 17:36:28 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>

struct s_for_export
{
	char	*command_name;
	char	*its_var;
} t_export;

enum
{
	OR,
	AND,
	D_QU,
	S_QU,
	EXPR,
	PIPE,
	SPACE,
	HEREDOC,
	REDIR_IN,
	BRKT_OPEN,
	BRKT_CLOSE,
	REDIR_OUT,
	REDIR_APPEND,
	DOLLAR,
} ;

// Execution Struct

typedef struct all_vars
{
	char	*env;
	int		index;
	int		increment;
	int		flag;
	char	*get_path;
	int		res_type;
	char	*allocation;
	char	*see_path;
	int		check_flag;
	int		this_path;
	int		for_total;
	char	*for_cd;
	char	*path_to;
	int		hold;
	char	*worck_with;
	char	*for_res;
	char	*make_sure;

}	all_vars;

// Struct for the linked list of the GC

typedef struct s_gc
{
	struct s_gc	*next;
	void		*address;
	int			fd;
}	t_gc;

// Struct for the Tracking of the list (CMDS) if 'NEEDED'

typedef struct s_tracker
{
    struct s_list	*head;
    struct s_list   *tail;
}	t_tracker;

// Struct for the Actual List (CMDS)

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*content;
	int				token_type;
}	t_list;

// tools

void	ft_bzero(void *s, size_t n);
void	*gc(int	size, int pass);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, int	len);
void	lst_size(t_tracker *holder);
char	*ft_strtrim(char *s, char *set);
char	*ft_strjoin(char *s1, char *s2);

//list tools

void	add_to_list_single(t_tracker *holder, char *input, int *start);
void	add_to_list_double(t_tracker *holder, char *input, int start, int *end);

// parcing

void	parcing(char *input);
char	**better_split(char *s);
char	*skip_empty_blocks(char *input);
char	*cut_string(char *string, int start, int finish);

// ******* --the functions Used in cd-- ******** 
void cd_function(char *path, char **env);
char **find_env(char *string, char **env);
int check_string(char *string, char *what_to_compare);
int count_word(char *string);
int le_count(char *string);
void putstr(char *string);
char *merge_path(char *string, char *path_add);
void paste(char string);
int check_if_to_turn(char *path, char **env);
int check_res_type(int res_type, char *path, char *for_cd);
int check_cd(char *path);
int merge_function(char *path, char **env);


// ***** --the function For the PWD function-- *****
void return_int_pwd_path(char **env, char *new_env);
int execve_function(char *if_ls);

// **** --the function For exit command 
int function_for_exit(char *string);

// *** --For the path-- ***
void show_path();

// *** --For echo function-- **
void check_for_echo(char *string);
char *remove_cd(char *string , char *ignore);

//for the export command 
void for_function(char *string);
int all_white(char string);
char *copy_for_remove_string(char *allocation ,char *string);
char *remove_string(char *string, char *to_move);
char *copy_till_charac(char *string , char to_here);
char *return_this(char *string, char *merge);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:21:05 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/08 20:57:12 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

// The List of tokens

enum
{
    OR,
    AND,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    PARA_OPEN,
    PARA_CLOSE,
    WORD,
    D_QU,
    S_QU,
    SPACE,
    HEREDOC,
    REDIR_APPEND,
    DOLLAR,
} ;

// Execution Struct

typedef struct all_vars {
    char    *env;
    int     index;
    int     increment;
    int     flag;
    char    *get_path;
    int     res_type;
    char    *allocation;
    char    *see_path;
    int     check_flag;
    int     this_path;
    int     for_total;
    char    *for_cd;
    char    *path_to;
} all_vars ;

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
	struct s_list *head;
	struct s_list *tail;
}	t_tracker;

// Struct for the Actual List (CMDS)

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*content;
	int				f_fd;
	int				is_visited;
	int				token_type;
}	t_list;


typedef struct s_tree_helper
{
	struct s_tree *root;
	struct s_tree *next_target;
}	t_th;

// Tree struct

typedef struct s_tree
{
	char			**content;
	int				token_type;
	int				f_fd;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// Struct to help in parcing

typedef struct s_pt
{
	int	s_bool;
	int	bo_bool;
	int	bc_bool;
	int	d_bool;
	int	e_bool;
	int	ex_bool;
}	t_pt;

// tools

void	ft_bzero(void *s, size_t n);
void	*gc(int	size, int pass);
int		ft_strncmp_2(char *s1, char *s2, int n);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, int	len);
void	lst_size(t_tracker *holder);
char	*ft_strtrim(char *s, char *set);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*get_next_line(int fd);
char	*ft_itoa(int n);

//list tools

void	add_to_list_single(t_tracker *holder, char *input, int *start);
void	add_to_list_double(t_tracker *holder, char *input, int start, int *end);
void	error_found();
int		compare(t_list *tmp, int token);
void	is_good(t_list *tmp, t_list *tmp_2);

// parcing

void	parcing(char *input);
char	**better_split(char *s);
char	*skip_empty_blocks(char *input);
char	*cut_string(char *string, int start, int finish);
void	check_validity(t_tracker *holder);
int		is_delimiter(char c, int pass);
char	*delete_quotes(char *string, int	quotes_type);
void	check_para(t_list *tmp);
void	check_para_2(t_list *tmp);
t_tree	*creat_leaf(t_list *node, t_th *tree_h);
t_list	*reset(t_list *node);
t_list	*search_for(t_list *node);
void	print_tree(t_tree *root, char *string);
void	merge_nodes(t_list *starting_point, \
t_list *ending_point, int new_type);
void	join_quotes(t_list **starting_point);
void	run_here_doc(t_list *tmp);

// tree

t_tree	*tree_generator(t_list *node, t_th *tree_h);

// execution

void find_env(char *string, char **env);
void cd_function(char *path);

#endif
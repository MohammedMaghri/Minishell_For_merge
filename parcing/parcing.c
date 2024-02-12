/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:10:41 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 22:07:03 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == 9 || c == '\'' || \
	c == '\"' || c == '&' || c == '|' || \
	c == '<' || c == '>' || c == 0 || c == '$');
}

void	set_tokens_2(t_list *tmp)
{
	if (!ft_strncmp(tmp->content, "&&", 2))
		tmp->token_type = AND;
	else if (!ft_strncmp(tmp->content, "\"", 1))
		tmp->token_type = D_QU;
	else if (!ft_strncmp(tmp->content, "\'", 1))
		tmp->token_type = S_QU;
	else if (!ft_strncmp(tmp->content, "(", 1))
		tmp->token_type = BRKT_OPEN;
	else if (!ft_strncmp(tmp->content, ")", 1))
		tmp->token_type = BRKT_CLOSE;
	else if (!ft_strncmp(tmp->content, "||", 2))
			tmp->token_type = OR;
	else
		tmp->token_type = EXPR;
}

void	set_tokens(t_tracker *holder)
{
	t_list	*tmp;

	tmp = holder->head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "<", 1))
			tmp->token_type = REDIR_IN;
		else if (!ft_strncmp(tmp->content, "<<", 2))
			tmp->token_type = HEREDOC;
		else if (!ft_strncmp(tmp->content, "$", 1))
			tmp->token_type = DOLLAR;
		else if (!ft_strncmp(tmp->content, ">>", 2))
			tmp->token_type = REDIR_APPEND;
		else if (!ft_strncmp(tmp->content, ">", 1))
			tmp->token_type = REDIR_OUT;
		else if (!ft_strncmp(tmp->content, " ", 1) || !ft_strncmp(tmp->content, "\t", 1))
			tmp->token_type = SPACE;
		else if (!ft_strncmp(tmp->content, "|", 1))
			tmp->token_type = PIPE;
		else
			set_tokens_2(tmp);
		tmp = tmp->next;
	}
}

void	set_list(t_tracker *holder, char	*input)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	input = skip_empty_blocks(input);
	l = ft_strlen(input);
	while (j <= l)
	{
		if (is_delimiter(input[j]))
		{
			if (i == j)
				add_to_list_single(holder, input, &j);
			else		
				add_to_list_double(holder, input, i, &j);
			i = j + 1;
		}
		j++;
	}
}

void	parcing(char *input)
{
	t_tracker	*holder;
	t_list		*tmp;

	holder = gc(sizeof(t_tracker), 0);
	holder->head = NULL;
	holder->tail = NULL;
	set_list(holder, input);
	tmp = holder->tail;
	holder->tail = holder->tail->prev;
	holder->tail->next = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	set_tokens(holder);
	lst_size(holder);
	tree_generator(holder->tail, tree_h);
	// print_tree(tree_h->root, "root\n");
}

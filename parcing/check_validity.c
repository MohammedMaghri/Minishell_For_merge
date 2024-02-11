/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:21:33 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 16:18:32 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare(t_list *tmp, int token)
{
	if (!tmp)
		return (0);
	if (tmp->token_type == token)
		return (1);
	return (0);
}

void	merge_nodes(t_list *starting_point, \
t_list *ending_point, int new_type)
{
	t_list	*tmp;

	tmp = starting_point->next;
	if (tmp == ending_point)
		starting_point->content = ft_strjoin(starting_point->content, \
		tmp->content);
	else
	{
		while (tmp != ending_point->next)
		{
			starting_point->content = ft_strjoin(starting_point->content, \
			tmp->content);
			tmp = tmp->next;
		}
	}
	starting_point->next = ending_point->next;
	if (ending_point && ending_point->next)
		ending_point->next->prev = starting_point;
	starting_point->token_type = new_type;
	if (!starting_point->next && starting_point->token_type != WORD)
	{printf("error in merg\n");
		error_found();}
	if (starting_point->token_type == HEREDOC)
		run_here_doc(tmp);
}

void	join_quotes(t_list **starting_point)
{
	t_list	*tmp;
	int		token_type;

	tmp = (*starting_point)->next;
	token_type = (*starting_point)->token_type;
	if ((*starting_point)->prev && (*starting_point)->prev->token_type == WORD)
		(*starting_point) = (*starting_point)->prev;
	while ((tmp->token_type != token_type))
		tmp = tmp->next;
	if (tmp->next && tmp->next->token_type == WORD)
		tmp = tmp->next;
	merge_nodes((*starting_point), tmp, WORD);
}

void	syntax_checker(t_list *tmp)
{
	t_list	*tmp_2;

	if ((!(tmp->next) && (tmp->token_type != D_QU && \
	tmp->token_type != S_QU)) || (!(tmp->prev) && (tmp->token_type != REDIR_IN \
	&& tmp->token_type != REDIR_OUT && tmp->token_type != HEREDOC)))
	{printf("syntax error _1 %s\n", tmp->content);
		error_found();}
	else
	{
		tmp_2 = tmp;
		tmp_2 = tmp_2->next;
		if (tmp->next->token_type == SPACE)
			tmp_2 = tmp_2->next;
		if (!ft_strncmp("||", tmp->content, 2) || !ft_strncmp("&&", \
		tmp->content, 2))
		{
			if ((tmp_2->token_type != WORD) && \
			(tmp_2->token_type != REDIR_OUT) && (tmp_2->token_type != \
			REDIR_APPEND) && (tmp_2->token_type != PARA_OPEN) \
			&& (tmp_2->token_type != PARA_CLOSE) \
			&& (tmp_2->token_type != DOLLAR))
			{printf("syntax error _2 %s\n", tmp_2->content);
				error_found();}
		}
		else
			is_good(tmp, tmp_2);
	}
}

void	check_validity(t_tracker *holder)
{
	static int	a;
	t_list		*tmp;

	tmp = holder->head;
	while (tmp)
	{
		if (compare(tmp, REDIR_IN) && compare(tmp->next, REDIR_IN))
			merge_nodes(tmp, tmp->next, HEREDOC);
		else if (compare(tmp, REDIR_OUT) && compare(tmp->next, REDIR_OUT))
			merge_nodes(tmp, tmp->next, REDIR_APPEND);
		else if (compare(tmp, PARA_OPEN) || compare(tmp, PARA_CLOSE))
			check_para(tmp);
		else if (compare(tmp, D_QU) || compare(tmp, S_QU))
			join_quotes(&tmp);
		else if ((tmp->token_type != WORD) && \
		(tmp->token_type != SPACE) && (tmp->token_type != DOLLAR) && \
		(tmp->token_type != PARA_CLOSE) && (tmp->token_type != PARA_OPEN))
			syntax_checker(tmp);
		tmp = tmp->next;
	}
	a++;
	if (a < 3)
		check_validity(holder);
}

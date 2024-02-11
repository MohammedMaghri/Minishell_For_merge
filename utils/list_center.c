/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:43:57 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/05 16:16:46 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		lst_size(t_tracker *holder)
{
	int i = 0;
	t_list *tmp  = holder->head;
	while (tmp)
	{
		printf("{%s} -> %d\n", tmp->content, tmp->token_type);
		tmp = tmp->next;
		i++;
	}
	printf("LST SIZE -> %d\n", i);
	i = 0;
	tmp = holder->tail;
	while (tmp)
	{
		tmp = tmp->prev;
		i++;
	}
	printf("LST SIZE -> %d\n", i);
}

void	link_new_nodes(t_tracker *holder, t_list *new_node_1, t_list *new_node_2)
{
	if (!(holder->head))
	{
		holder->head = new_node_1;
		new_node_1->next = new_node_2;
		new_node_2->prev = holder->head;
		holder->tail = new_node_2;
		return ;
	}
	holder->tail->next = new_node_1;
	new_node_1->next = new_node_2;
	new_node_1->prev = holder->tail;
	new_node_2->prev = new_node_1;
	holder->tail = new_node_2;
}

void	link_the_single_node(t_tracker *holder, t_list *new_node)
{
	if (!(holder->head))
	{
		holder->head = new_node;
		holder->tail = new_node;
		return ;
	}
	holder->tail->next = new_node;
	new_node->prev = holder->tail;
	holder->tail = new_node;
}

void	add_to_list_single(t_tracker *holder, char *input, int *start)
{
	t_list	*new_node;

	new_node = gc(sizeof(t_list), 0);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (input[*start] == '|' && input[*start + 1] == '|')
		new_node->content = ft_substr("||", 0, 2);
	else if (input[*start] == '&' && input[*start + 1] == '&')
		new_node->content = ft_substr("&&", 0, 2);
	else
		new_node->content = ft_substr(input, *start, 1);
	if ((input[*start] == '|' && input[*start + 1] == '|') || \
	(input[*start] == '&' && input[*start + 1] == '&'))
		*start += 1;
	link_the_single_node(holder, new_node);
}

void	add_to_list_double(t_tracker *holder, char *input, int start, int *end)
{
	t_list	*new_node_1;
	t_list	*new_node_2;

	new_node_1 = gc(sizeof(t_list), 0);
	new_node_1->next = NULL;
	new_node_1->prev = NULL;
	new_node_2 = gc(sizeof(t_list), 0);
	new_node_2->next = NULL;
	new_node_2->prev = NULL;
	new_node_1->content = ft_substr(input, start, (*end - start));
	if (input[*end] == '|' && input[*end + 1] == '|')
		new_node_2->content = ft_substr("||", 0, 2);
	else if (input[*end] == '&' && input[*end + 1] == '&')
		new_node_2->content = ft_substr("&&", 0, 2);
	else
		new_node_2->content = ft_substr(input, *end, 1);
	if ((input[*end] == '|' && input[*end + 1] == '|') || \
	(input[*end] == '&' && input[*end + 1] == '&'))
		*end += 1;
	link_new_nodes(holder, new_node_1, new_node_2);
}

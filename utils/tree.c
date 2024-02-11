/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:52:38 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 21:52:41 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(t_tree *root, char *string)
{
	int i = -1;
	if (!root)
		return ;
	while (root->content[++i])
		printf("^^^^%s        %s^^^^       %d\n", string, root->content[i], i);
	print_tree(root->left, "left");
		printf("%s\n", root->content[0]);
	print_tree(root->right, "right");
}

void	fill_content(t_list *tmp, t_tree *leaf)
{
	t_list	*tmp_2;
	t_list	*tmp_3;
	int		i;

	i = 1;
	tmp = reset(tmp);
	tmp_2 = reset(tmp);
	tmp->is_visited = 1;
	while (tmp->prev && tmp->prev->is_visited != 1)
	{
		tmp = tmp->prev;
		tmp->is_visited = 1;
		i++;
	}
	leaf->content = gc(sizeof(char *) * (i + 1), 0);
	tmp_3 = tmp;
	i = 0;
	while (tmp_3 != tmp_2->next)
	{
		leaf->content[i++] = tmp_3->content;
		tmp_3 = tmp_3->next;
	}
	leaf->content[i] = NULL;
}

t_tree	*creat_leaf(t_list *node, t_th *tree_h)
{
	t_tree	*leaf;

	if (!node)
		return (NULL);
	leaf = gc(sizeof(t_tree), 0);
	leaf->content = gc(sizeof(char *)*2, 0);
	leaf->content[0] = node->content;
	leaf->content[1] = NULL;
	if (node->token_type == WORD)
		fill_content(node, leaf);
	node->is_visited = 1;
	if (!tree_h->root)
		tree_h->root = leaf;
	leaf->token_type = node->token_type;
	leaf->left = NULL;
	leaf->right = NULL;
	if (node->prev && !(node->prev->is_visited))
		leaf->left = tree_generator(node->prev, tree_h);
	if (node->next && !(node->next->is_visited))
		leaf->right = tree_generator(node->next, tree_h);
	return (leaf);
}

t_list	*reset(t_list *node)
{
	while (node->next && !(node->next->is_visited))
		node = node->next;
	return (node);
}

t_list	*search_for(t_list *node)
{
	int	token_type;
	int	var;

	token_type = 0;
	while (++token_type < 8)
	{
		var = 15;
		if (token_type == 1)
			var = 0;
		if (token_type == 3)
			var = 4;
		if (token_type == 5)
			var = 6;
		node = reset(node);
		while (node->prev && node->prev->is_visited != 1 && \
		node->token_type != token_type && node->token_type != var)
			node = node->prev;
		if (node && (node->token_type == token_type || node->token_type == var))
			return (node);
	}
	return (NULL);
}

t_tree	*tree_generator(t_list *node, t_th *tree_h)
{
	t_tree	*leaf;

	if (!node)
		return (NULL);
	leaf = creat_leaf(search_for(node), tree_h);
	return (leaf);
}

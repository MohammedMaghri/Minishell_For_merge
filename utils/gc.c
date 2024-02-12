/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:20:28 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/04 15:28:47 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = 0;
		s++;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	if (count * size >= LONG_MAX)
		return (NULL);
	s = malloc(count * size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

void	clear_all(t_gc *head)
{
	t_gc *tmp;

	while (head)
	{
		tmp = head->next;
		if (head->address)
			free(head->address);
		if (head->fd)
			close(head->fd);
		free(head);
		head = tmp;
	}
}

void	*gc(int	size, int pass)
{
	static t_gc *head;
	t_gc		*node;
	void		*address;
	int			fd;

	fd = 0;
	address = NULL;
	if (!pass || pass == 3)
	{
		node = ft_calloc(sizeof(t_gc), 1);
		if (!pass)
			address = ft_calloc(size, 1);
		else
			fd = size;
		if (!node || !address)
			return (printf("error in allocation\n"), \
			clear_all(head), NULL);
		node->next = head;
		node->address = address;
		node->fd = fd;
		head = node;
		return (address);
	}
	return (clear_all(head), NULL);
}

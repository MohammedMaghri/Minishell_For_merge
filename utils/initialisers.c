/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:21:39 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 18:25:46 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_fork(void)
{
	int	id;

	id = fork();
	if (id == -1)
		return (printf("faille in fork\n"), gc(0, 2), 1);
	return (id);
}

int	*my_pipe(void)
{
	int	*p;

	p = gc(sizeof(int) * 2, 0);
	if (pipe(p) == -1)
		return (printf("faille in pipe\n"), gc(0, 2), NULL);
	gc(p[0], 3);
	gc(p[1], 3);
	return (p);
}

int	my_open_input(t_tree *leaf)
{
	int	fd;

	fd = open(leaf->av[1], O_RDONLY);
	if (fd == -1 && !access(leaf->av[1], F_OK) \
	&& access(leaf->av[1], R_OK) == -1)
		return (perror("permission denied"), gc(0, 2), 1);
	else if (fd == -1)
		return (perror("invalid file"), gc(0, 2), 1);
	return (fd);
}

int	my_open_output(t_tree *leaf)
{
	int	fd;
	int	var;

	var = 0x0400;
	if (leaf->token_type == HEREDOC)
		var = 0x0008;
	fd = open(leaf->av[leaf->ac - 1], O_WRONLY | O_CREAT | var, 0777);
	if (fd == -1 && !access(leaf->av[leaf->ac - 1], F_OK) \
	&& access(leaf->av[leaf->ac - 1], W_OK) == -1)
		return (perror("permission denied"), -2);
	if (fd == -1)
		return (perror("invalid fd"), close_fds(data), gc(0, 2), 1);
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:52:56 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 18:24:16 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_tmp(char *tmp, int fd)
{
	int	i;

	i = -1;
	if (!ft_strlen(tmp))
	{
		/// Should handel the case
		printf("process killed\n");
		gc(0, 2);
	}
	while (tmp[++i])
		write(fd, &tmp[i], 1);
}

int	open_here_doc(t_list *tmp)
{
	char	*name;
	int		fd;
	int		i;

	i = 0;
	name = ft_substr(".here_doc", 0, 9);
	while (!access(name, F_OK))
		name = ft_strjoin(name, ft_itoa(++i));
	fd = open(name, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		return (printf("Error in opening Here Doc\n"), gc(0, 2), 1);
	gc(fd, 3);
	tmp->f_fd = open(name, O_RDWR);
	if (tmp->f_fd == -1)
		return (unlink(name), printf("Error in opening Here Doc\n"), \
		gc(0, 2), 1);
	gc(tmp->f_fd, 3);
	unlink(name);
	return (fd);
}

void	run_here_doc(t_list *tmp)
{
	char	*in;
	char	*del;
	int		fd;

	fd = 0;
	fd = open_here_doc(tmp);
	if (tmp->next->token_type == SPACE)
		tmp = tmp->next;
	del = ft_strjoin(tmp->next->content, "\n");
	while (1)
	{
		write(1, "here_> ", 8);
		in = get_next_line(0);
		if (!ft_strncmp_2(in, del, ft_strlen(del)))
			break ;
		put_tmp(in, fd);
	}
	close(fd);
}

void	is_good(t_list *tmp, t_list *tmp_2)
{
	if (((compare(tmp, PIPE) || compare(tmp, REDIR_IN) || compare(tmp, \
	REDIR_OUT)) || compare(tmp, HEREDOC)) && \
	(compare(tmp_2, AND) || compare(tmp_2, OR)))
	{
		printf("error is good_1");
		error_found();
	}
	if ((compare(tmp, REDIR_IN) || \
	compare(tmp, REDIR_OUT)) && (compare(tmp_2, \
	REDIR_IN) || compare(tmp_2, REDIR_OUT) || compare(tmp_2, \
	PARA_OPEN) || compare(tmp_2, PARA_CLOSE)))
	{
		printf("error is good_2");
		error_found();
	}
}

void	check_para(t_list *tmp)
{
	t_list	*tmp_2;

	if (tmp->token_type == PARA_OPEN)
	{
		if (tmp->prev)
		{
			tmp_2 = tmp->prev;
			if (tmp_2->prev && tmp_2->token_type == SPACE)
				tmp_2 = tmp_2->prev;
			if (tmp_2->token_type == WORD || tmp_2->token_type == PARA_CLOSE || \
			tmp_2->token_type == D_QU || tmp_2->token_type == S_QU)
			{
				printf("PAR _1\n");
				error_found();
			}
		}
		else if (tmp->next->token_type == PARA_CLOSE || \
		tmp->next->token_type == D_QU || tmp->next->token_type == S_QU)
			{printf("PAR _2\n");
			error_found();}
	}
	else
		check_para_2(tmp);
}

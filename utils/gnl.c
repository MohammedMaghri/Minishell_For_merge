/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:35:17 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 16:19:26 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_set_holder(char *holder)
{
	char	*newholder;
	int		hl;
	int		l;
	int		i;
	int		j;

	i = 0;
	j = 0;
	hl = ft_strlen(holder);
	while (holder[i] && holder[i] != '\n')
		i++;
	if (holder[i] == '\n')
		i++;
	l = hl - i;
	newholder = (char *)gc(l + 1, 0);
	if (!newholder)
		return (NULL);
	while (j < l)
		newholder[j++] = holder[i++];
	newholder[j] = '\0';
	return (newholder);
}

char	*ft_set_line(char *holder)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (holder[i] == '\n')
		i++;
	res = (char *)gc(i + 1, 0);
	if (!res)
		return (NULL);
	while (j < i)
	{
		res[j] = holder[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_read(char *holder, int fd)
{
	char	reader[100 + 1];
	int		counter;

	while (!ft_strchr(holder, '\n'))
	{
		counter = read(fd, reader, 100);
		if (counter <= 0)
			break ;
		reader[counter] = '\0';
		holder = ft_strjoin(holder, reader);
	}
	if (holder == NULL)
		return (NULL);
	if (read(fd, NULL, 0) == -1 || holder[0] == '\0')
		return (NULL);
	return (holder);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*res;

	if (read(fd, 0, 0) == -1)
		return (printf("Error in read\n"), gc(0, 2), NULL);
	holder = ft_read(holder, fd);
	if (!holder)
		return (NULL);
	res = ft_set_line(holder);
	if (!res)
		return (NULL);
	holder = ft_set_holder(holder);
	if (!holder)
		return (NULL);
	return (res);
}

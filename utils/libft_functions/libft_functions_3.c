/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:15 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 16:18:47 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)b = (unsigned char)c;
		b++;
		i++;
	}
	return (b - i);
}

static	void	ft_stockn(char *str, int n, int *p)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		ln = -ln;
		ft_memset((str + *p), '-', 1);
		*p += 1;
	}
	if (ln > 9)
	{
		ft_stockn(str, ln / 10, p);
		ft_stockn(str, ln % 10, p);
	}
	else
	{
		ft_memset((str + *p), (ln + '0'), 1);
		*p += 1;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	ln;
	int		s;
	int		p;

	ln = n;
	p = 0;
	s = 0;
	if (ln < 0)
	{
		ln = -ln;
		s++;
	}
	while (ln >= 10)
	{
		ln /= 10;
		s++;
	}
	s++;
	str = gc(s + 1, 0);
	ft_stockn(str, n, &p);
	str[s] = '\0';
	return (str);
}

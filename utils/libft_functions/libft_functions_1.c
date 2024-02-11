/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:43:46 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 16:18:55 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strtrim(char *s, char *set)
{
	char	*str;
	int		i;
	int		l;

	i = 0;
	l = ft_strlen(s);
	while (ft_strchr((char *)set, s[i]) && l != 0)
		i++;
	while ((l - 1) > 0 && ft_strchr((char *)set, s[l - 1]))
		l--;
	str = ft_substr(s, i, (l - i));
	return (str);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	if (start + len > (unsigned int)ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	if (len + 1 < 0)
	{printf("substr\n");
		error_found();}
	sub = gc(len + 1, 0);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

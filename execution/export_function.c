/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:33:00 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 16:31:31 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_the_same(char *string, char *make_sure)
{
	all_vars	ch;

	ch.index = 0;
	ch.increment = 0;
	ch.flag = 0;
	ch.hold = 0;
	if (string[ch.index] == make_sure[0])
	{
		ch.index++;
		ch.increment++;
		ch.flag++;
		while (string[ch.index] && ch.increment <= 5)
		{
			if (string[ch.index] == make_sure[ch.increment])
				ch.flag++;
			ch.increment++;
			ch.index++ ;
		}
		if (ch.flag == le_count(make_sure))
			ch.hold = 1;
	}
	return (ch.hold);
}

char	*copy_for_export(char *string, char *for_res)
{
	int	index ;
	int	increment;

	increment = 0;
	index = 0;
	while (string[index])
	{
		if (string[index] == '"')
			index++ ;
		for_res[increment] = string[index];
		increment++ ;
		index++ ;
	}
	for_res[increment] = '\0';
	return (for_res);
}

char	*var_turn(char *string, char *worck_with)
{
	worck_with = remove_string(string, "export");
	worck_with = copy_till_charac(worck_with, '=');
	return (worck_with);
}

char	*for_the_while(char *string, char *for_res)
{
	all_vars	func;

	while (string[func.index])
	{
		if (string[func.index] == '=')
		{
			if (string[func.index + 1] == ' ')
				return (NULL);
			func.index++ ;
			for_res = copy_for_export(&string[func.index], for_res);
			break ;
		}
		func.index++ ;
	}
	return (func.for_res);
}

void	for_function(char *string)
{
	all_vars	f;

	f.index = 0;
	while (string[f.index] && string[f.index] == ' ')
		f.index++ ;
	if (1 == 1 && check_if_the_same(&string[f.index], "export") == 1)
	{
		f.index = 0;
		f.for_res = malloc(1000000);
		f.worck_with = var_turn(string, f.worck_with);
		while (string[f.index])
		{
			if (string[f.index] == '=')
			{
				if (string[f.index + 1] == ' ')
					return ;
				f.index++ ;
				f.for_res = copy_for_export(&string[f.index], f.for_res);
				break ;
			}
			f.index++ ;
		}
		printf("worck == %s\n", return_this(f.worck_with, "$"));
		printf("res ==   %s\n", f.for_res);
	}
}

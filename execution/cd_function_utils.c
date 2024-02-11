/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:28:11 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 17:37:38 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_to_turn(char *path, char **env)
{
	all_vars	for_func;
	int			index;

	index = 0;
	if (count_word(path) == 1)
	{
		if (check_string(path, "cd") != 0)
			return (-1);
		for_func.res_type = chdir(path);
		for_func.env = getenv("USER");
		for_func.this_path = chdir(merge_path("/Users/", for_func.env));
		return_int_pwd_path(env, &for_func.see_path[index]);
		return (-1);
	}
	return (0);
}

int	check_res_type(int res_type, char *path, char *for_cd)
{
	if (res_type == -1 && count_word(path) == 2)
	{
		putstr("cd: no such file or directory: \n");
		putstr(for_cd);
		return (-1);
	}
	else if (res_type == -1 && count_word(path) > 2)
	{
		putstr("cd: string not in pwd: \n");
		putstr(for_cd);
		return (-1);
	}
	return (0);
}

int	check_cd(char *path)
{
	int	index ;

	index = 0;
	while (path[index] && path[index] == ' ')
		index++ ;
	if (path[index] == 'c')
	{
		index++ ;
		if (path[index] != 'd')
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	merge_function(char *path, char **env)
{
	all_vars	for_func;

	for_func.hold = check_cd(path);
	if (for_func.hold == -1)
		return (-1);
	for_func.flag = check_if_to_turn(path, env);
	if (for_func.flag == -1)
		return (-1);
	return (0);
}

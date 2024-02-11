/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:33:18 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 18:04:14 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_path(char *string, char *path_add)
{
	all_vars	path;

	path.index = 0;
	path.increment = 0;
	path.allocation = malloc(sizeof(char) * \
	(le_count(string) + le_count(path_add) + 1));
	if (!path.allocation)
		return (NULL);
	while (string[path.index])
	{
		path.allocation[path.increment] = string[path.index];
		path.increment++;
		path.index++ ;
	}
	path.index = 0;
	path.allocation[path.increment] = '/';
	path.increment++;
	while (path_add[path.index])
	{
		path.allocation[path.increment] = path_add[path.index];
		path.increment++;
		path.index++ ;
	}
	path.allocation[path.increment] = '\0';
	return (path.allocation);
}

char	*for_remove_cd_func(char *string, char *allocation)
{
	all_vars	every;

	every.index = 0;
	every.increment = 0;
	while (string[every.index] && string[every.index] \
	&& string[every.index] != ' ')
	{
		allocation[every.increment] = string[every.index];
		every.index++ ;
		every.increment++ ;
	}
	allocation[every.increment] = '\0';
	return (allocation);
}

char	*remove_cd(char *string, char *ignore)
{
	all_vars	every;

	every.index = 0;
	every.increment = 0;
	every.for_total = le_count(ignore);
	every.allocation = malloc(sizeof(char) * le_count(string));
	if (!every.allocation)
		return (NULL);
	while (string[every.index] && string[every.index] == ' ')
		every.index++ ;
	while (string[every.index] != ' ' && every.for_total != 0)
	{
		if (string[every.index] == ignore[every.increment])
		{
			every.index++ ;
			every.increment++ ;
		}
		every.for_total--;
	}
	while (string[every.index] && string[every.index] == ' ')
		every.index++ ;
	every.allocation = for_remove_cd_func(&string[every.index], \
	every.allocation);
	return (every.allocation);
}

void	cd_function(char *path, char **env)
{
	all_vars	for_func;

	for_func.index = 0;
	for_func.hold = check_cd(path);
	for_func.flag = check_if_to_turn(path, env);
	if (for_func.flag == -1 || for_func.hold == -1)
		return ;
	if (le_count(path) > 2)
	{
		for_func.see_path = malloc(1000);
		if (!for_func.see_path)
			return ;
		for_func.get_path = getcwd(for_func.see_path, 1000);
		for_func.for_cd = remove_cd(path, "cd");
		for_func.path_to = merge_path(for_func.get_path, for_func.for_cd);
		for_func.res_type = chdir(for_func.path_to);
		return_int_pwd_path(env, &for_func.see_path[for_func.index]);
		if (check_res_type(for_func.res_type, path, for_func.for_cd) == -1)
			return ;
	}
	if (for_func.check_flag == -1)
		printf("cd: no such file or directory:");
	return ;
}

char	**find_env(char *string, char **env)
{
	int		index ;
	char	*env_vars ;

	index = 0;
	env_vars = env[index];
	if (check_string(string, "env") == 0)
	{
		while (env_vars != NULL)
		{
			putstr(env_vars);
			paste('\n');
			index++ ;
			env_vars = env[index];
		}

	}
	return (env);
}

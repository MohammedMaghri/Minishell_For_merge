/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_empty_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:16:32 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/05 16:27:18 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cut_string(char *string, int start, int finish)
{
	char	*part_1;
	char	*part_2;
	int		before_length;
	int		i;

	i = start - 1;
	before_length = ft_strlen(string);
	while (++i < finish)
		;
	part_1 = ft_substr(string, 0, start + 1);
	part_2 = ft_substr(string, finish, ft_strlen(string) - finish);
	return(ft_strjoin(part_1, part_2));
}

char *skip_empty_blocks(char *input)
{
	char	*new_input;
	int		i;
	int		j;

	i = 0;
	new_input = ft_strtrim(input, " \t");
	free(input);
	while (new_input[i])
	{
		if (new_input[i] == 32 || new_input[i] == 9)
		{
			j = i;
			while (new_input[j] && (new_input[j] == 32 || new_input[j] == 9))
				j++;
			new_input = cut_string(new_input, i, j);
			i++;
		}
		else
			i++;
	}
	return (new_input);
}
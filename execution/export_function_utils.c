/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_function_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:44:33 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 16:24:55 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_white(char string)
{
	if (string == ' ')
		return (-1);
	else if (string == '\t')
		return (-1);
	else if (string >= 9 && string <= 13)
		return (-1);
	else if (string == '\0')
		return (-1);
	return (0);
}

char	*copy_for_remove_string(char *allocation, char *string)
{
	all_vars	copy;

	copy.increment = 0;
	copy.index = 0;
	while (string[copy.index])
	{
		allocation[copy.increment] = string[copy.index];
		copy.increment++ ;
		copy.index++ ;
	}
	allocation[copy.increment] = '\0';
	return (allocation);
}

char	*remove_string(char *string, char *to_move)
{
	all_vars	rem;

	rem.increment = 0;
	rem.index = 0;
	rem.allocation = malloc(1000000);
	while (string[rem.index] && all_white(string[rem.index]) == -1)
		rem.index++ ;
	if (string[rem.index] == to_move[0])
	{
		rem.index++ ;
		rem.increment++ ;
		while (string[rem.index] == to_move[rem.increment])
		{
			rem.index++ ;
			rem.increment++ ;
		}
	}
	rem.increment = 0;
	if (string[rem.index + 1] != '\0')
		rem.allocation = copy_for_remove_string(rem.allocation, \
		&string[rem.index]);
	return (rem.allocation);
}

char	*copy_till_charac(char *string, char to_here)
{
	all_vars	till;

	till.index = 0;
	till.allocation = malloc(100000);
	while (string[till.index])
	{
		if (string[till.index] == to_here)
			break ;
		till.allocation[till.index] = string[till.index];
		till.index++ ;
	}
	till.allocation[till.index] = '\0';
	return (till.allocation);
}

char	*return_this(char *string, char *merge)
{
	all_vars	till;

	till.index = 0;
	till.increment = 0;
	till.allocation = malloc(10000);
	while (merge[till.index])
	{
		till.allocation[till.increment] = merge[till.index];
		till.index++ ;
		till.increment++;
	}
	while (string[till.index])
	{
		till.allocation[till.increment] = string[till.index];
		till.increment++;
		till.index++;
	}
	till.allocation[till.increment] = '\0';
	return (till.allocation);
}

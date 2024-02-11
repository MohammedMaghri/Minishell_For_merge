/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:16:59 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 12:07:13 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak(void)
{
	system ("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	// int		id;

	if (ac != 1)
		return (0);
	// atexit(leak);
	(void)env;
	(void)av;
	(void)ac;
	while (1)
	{
		input = readline("_> ");
		if (input && input[0])
		{
			add_history(input);
			// id = fork();
			// if (!id)
				parcing(input);
			// else
			// 	while (wait(NULL) != -1)
			// 		;
		}
	}
	return (0);
}

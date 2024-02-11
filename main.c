/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:16:59 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 17:45:07 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input ;
    char	**envirment;
    int		res;

	if (ac != 1)
		return (0);
	(void)env;
	(void)av;
	(void)ac;
    int flag = 0;
    pid_t pid;

    while (1)
    {
        input = readline("➜ Bash :");
        for_function(input);
        if ((check_string("exit",input)) == 0)
        {
            printf("exit\n");
            exit(0);
        }
        if (flag == -1)
            exit(0);
        if (input)
        {
            check_for_echo(input);
            pid = fork();
            if (pid == 0)
            {
                envirment = find_env(input, env);
                show_path(input);
                res = execve_function(input);
                cd_function(input, envirment);
            }
            while (wait(NULL) != -1);
        }
    }
    exit(0);
}
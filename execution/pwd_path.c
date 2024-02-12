/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:23:35 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/06 13:50:29 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void return_int_pwd_path(char **env, char *new_env)
{
    all_vars for_pwd;

    for_pwd.index = 0;
    for_pwd.increment = 0;
    for_pwd.flag = 0;
    char *pwd = "PWD";
    while (env[for_pwd.index])
    {
        while (for_pwd.increment < 3)
        {
            if (env[for_pwd.index][for_pwd.increment] == pwd[for_pwd.increment])
                for_pwd.flag++ ;
            for_pwd.increment++ ;
        }
        if (for_pwd.flag == 3)
            {
                env[for_pwd.index] = merge_path("PWD=", new_env);
                return ;
            }
        for_pwd.increment = 0;
        for_pwd.flag = 0;
        for_pwd.index++ ;
    }
}
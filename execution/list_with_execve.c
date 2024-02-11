/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_with_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:35 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/06 18:23:53 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execve_function(char *if_ls)
{
    char *binls = "/bin/ls";
    char *twode[] = {"/bin/ls", NULL};
    if (check_string(if_ls, "ls") == 0)
    {
        if ((execve(binls, twode, NULL)) == -1)
            return (-1);
    }
    return (0);
}
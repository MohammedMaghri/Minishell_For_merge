/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_show.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:14:37 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/06 18:19:49 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void show_path(char *string)
{
    char *current_dir;

    current_dir = malloc(10000);
    if (check_string(string, "pwd") == 0)
        printf("%s\n", getcwd(current_dir, 10000));
    return ;
}
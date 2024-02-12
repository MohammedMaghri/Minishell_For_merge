/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:27:00 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/06 12:48:29 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "minishell.h"

void ls_function()
{
    all_vars for_ls;

    for_ls.path_put = malloc(1000);
    struct dirent *entry;
    DIR *directory;
    directory = opendir(for_ls.path_put);
    while ((entry = readdir(directory)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }
}
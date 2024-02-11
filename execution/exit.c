/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:16:56 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/06 17:48:08 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int function_for_exit(char *string)
{
    if ((check_string("exit", string)) == 0)
    {
        printf("exit");
        return (-1);
    }
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:53:32 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/05 19:05:02 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_string(char *string, char *what_to_compare)
{
    int index = 0;
    int increment = 0;
    int flag = 0;
    while(string[index] && string[index] == ' ')
        index++ ;
    while (string[index])
    {
        if (string[index] == what_to_compare[increment])
            flag++ ;
        index++ ;
        increment++;
    }
    if (flag == le_count(what_to_compare))
        return(0);
    return (-1);
}

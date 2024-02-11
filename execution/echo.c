/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:04:34 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/11 17:48:35 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_echo(char *string)
{
	all_vars	for_echo;
	char *echo = "echo ";
	for_echo.flag = 0;
    for_echo.index = 0;
    for_echo.increment = 0;
    while (string[for_echo.index] && string[for_echo.index] == ' ')
        for_echo.index++ ;
    while (for_echo.increment < 5)
    {
        if (string[for_echo.index] == echo[for_echo.increment])
            for_echo.flag++ ;
        for_echo.index++;
        for_echo.increment++;
    }
    if (for_echo.flag == 5)
    {
        while (string[for_echo.index] && string[for_echo.index] == ' ')
            for_echo.index++ ;
        if (string[for_echo.index] == '-')
            {
                if (string[for_echo.index + 1] == 'n' && (string[for_echo.index + 2] == ' ' || string[for_echo.index + 2] == '\0'))
                    {
                        for_echo.index++ ;
                        for_echo.index++ ;
                        printf("%s", &string[for_echo.index]);
                        return ;
                    } 
            }
            printf("%s\n", &string[for_echo.index]);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_basic_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:54:45 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/05 19:04:58 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void paste(char string)
{
    write(1,&string,1);
}

void putstr(char *string)
{
    while(*string)
        write(1 , string++ ,1);
}

int le_count(char *string)
{
    int index = 0 ;
    while (string[index])
        index++ ;
    return (index);
}

int count_word(char *string)
{
    int index = 0;
    int flag = 0;
    while (string[index])
    {
        if (string[index] && string[index] == ' ')
            index++ ;
        else 
        {
            flag++ ;
            while(string[index] && string[index] != ' ')
                index++ ;
        }
    }
    return (flag);
}
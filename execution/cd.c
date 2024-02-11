/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:33:18 by mmaghri           #+#    #+#             */
/*   Updated: 2024/02/07 18:31:47 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int count_WORD(char *string)
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
char *merge_path(char *string, char *path_add)
{
    all_vars path;

    path.index = 0;
    path.increment = 0;
    path.allocation = malloc(sizeof(char) * (le_count(string) + le_count(path_add) + 1));
    if(!path.allocation)
        return (NULL);
    while (string[path.index])
    {
        path.allocation[path.increment] = string[path.index];
        path.increment++;
        path.index++ ;
    }
    path.index = 0;
    path.allocation[path.increment] = '/';
    path.increment++;
    while (path_add[path.index])
    {
        path.allocation[path.increment] = path_add[path.index];
        path.increment++;
        path.index++ ;
    }
    free(path_add);
    path.allocation[path.increment] = '\0';
    return (path.allocation);
}
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
    printf("%d", flag);
    if (flag == le_count(what_to_compare))
        return(0);
    return (-1);
}
void paste(char string)
{
    write(1,&string,1);
}
char *remove_cd(char *string , char *ignore)
{
    all_vars every;
    every.index = 0;
    every.increment = 0;
    every.for_total = le_count(ignore);
    every.allocation = malloc(sizeof(char) * le_count(string));
    if (!every.allocation)
        return (NULL);
    while (string[every.index] && string[every.index] == ' ')
        every.index++ ;
    while (string[every.index] != ' ' && every.for_total != 0)
    {
        if (string[every.index] == ignore[every.increment])
        {
            every.index++ ;
            every.increment++ ;
        }
        every.for_total--;
    }
    while (string[every.index] &&  string[every.index] == ' ')
        every.index++ ;
    every.increment = 0;
    while (string[every.index] && string[every.index] && string[every.index] != ' ')
    {
        every.allocation[every.increment] = string[every.index];
        every.index++ ;
        every.increment++ ;
    }
    every.allocation[every.increment] = '\0';
    return (every.allocation);
}

void cd_function(char *path)
{
    all_vars for_func;
    for_func.see_path = malloc(1000);
    if (!for_func.see_path)
        return ;
    if (count_WORD(path) == 1)
        {
            if (check_string(path, "cd") != 0)
                return ;
            printf("here");
            for_func.res_type = chdir(path);
            for_func.env = getenv("USER");
            for_func.this_path = chdir(merge_path("/Users", for_func.env));
            return ;
        }
    else if (le_count(path) > 2)
    {
       for_func.get_path = getcwd(for_func.see_path, 1000);
       for_func.for_cd = remove_cd(path, "cd");
       for_func.path_to = merge_path(for_func.get_path, for_func.for_cd);
       for_func.res_type = chdir(for_func.path_to);
       if (for_func.res_type == -1 && count_WORD(path) == 2)
       {
        putstr("cd: no such file or directory: ");
        putstr(for_func.for_cd);
        exit(1);
        }
       else if (for_func.res_type == -1 && count_WORD(path) > 2)
       {
        putstr("cd: string not in pwd: ");
        putstr(for_func.for_cd);
        exit(1);
       }
    }
    if (for_func.check_flag == -1)
    {
        putstr("cd: no such file or directory: ");
        exit(1);
    }
    printf("%s", getcwd(for_func.see_path, 1000));
    return ;
}
void find_env(char *string, char **env)
{
    int index = 0;
    char *env_vars ;
    env_vars = env[index];
    if (check_string(string, "env") == 0)
    {
        while (env_vars != NULL)
        {
            putstr(env_vars);
            paste('\n');
            index++ ;
            env_vars = env[index];
        }
    }
    paste('\n');
}

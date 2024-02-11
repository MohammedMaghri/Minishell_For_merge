/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_empty_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:16:32 by mlouazir          #+#    #+#             */
/*   Updated: 2024/02/11 19:00:21 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*delete_quotes(char *string, int quotes_type)
// {
// 	char	*res;
// 	char	*c;
// 	int		i;

// 	i = -1;
// 	c = gc(2, 0);
// 	c[1] = 0;
// 	if (quotes_type == D_QU)
// 		c[0] = '\"';
// 	else
// 		c[0] = '\'';
// 	res = ft_strtrim(string, c);
// 	while (res[++i])
// 	{
// 		if (res[i] == c[0])
// 		{
// 			res = cut_string(res, i - 1, i + 1);
// 			i = -1;
// 		}
// 	}
// 	return (res);
// }
// 

void	check_para_2(t_list *tmp)
{
	t_list	*tmp_2;

	if (tmp->next)
	{
		tmp_2 = tmp->next;
		if (tmp_2->next && tmp_2->token_type == SPACE)
			tmp_2 = tmp_2->next;
		if (tmp_2->token_type == WORD || tmp_2->token_type == PARA_OPEN \
		|| tmp_2->token_type == D_QU || tmp_2->token_type == S_QU)
			{printf("PAR _3\n");
			error_found();}	
	}
	else if (tmp->prev->token_type == PARA_CLOSE || \
	tmp->prev->token_type == D_QU || tmp->prev->token_type == S_QU)
		{printf("PAR _4\n");
		error_found();}
}

char	*cut_string(char *string, int start, int finish)
{
	char	*part_1;
	char	*part_2;
	int		before_length;

	before_length = ft_strlen(string);
	part_1 = ft_substr(string, 0, start + 1);
	part_2 = ft_substr(string, finish, ft_strlen(string) - finish);
	return (ft_strjoin(part_1, part_2));
}

void	check_if_ended(t_pt *bool, int pass)
{
	if (pass && (bool->d_bool || bool->s_bool || \
	(bool->bo_bool - bool->bc_bool)))
	{
		printf("bool error\n");
		error_found();
	}
	else
	{
		bool->s_bool = 0;
		bool->d_bool = 0;
		bool->e_bool = 0;
		bool->ex_bool = 0;
		bool->bo_bool = 0;
		bool->bc_bool = 0;
	}
}

void	check_bool(char *new_input, int index, t_pt *bool)
{
	if ((new_input[index] == '\'') && !(bool->s_bool) && !(bool->d_bool))
		bool->s_bool = 1;
	else if ((new_input[index] == '\"') && !(bool->s_bool) && !(bool->d_bool))
		bool->d_bool = 1;
	else if ((new_input[index] == '\'') && (bool->s_bool) && !(bool->d_bool))
		bool->s_bool = 0;
	else if ((new_input[index] == '\"') && !(bool->s_bool) && (bool->d_bool))
		bool->d_bool = 0;
	else if (new_input[index] == '(' && !(bool->s_bool) && !(bool->d_bool))
		bool->bo_bool++;
	else if (new_input[index] == ')' && bool->bo_bool)
		bool->bc_bool++;
	else if (!ft_strncmp(new_input + index, "echo", 4) && !(bool->e_bool))
		bool->e_bool = 1;
	else if (!ft_strncmp(new_input + index, "export", 6) && !(bool->ex_bool))
		bool->ex_bool = 1;
	else if (is_delimiter(new_input[index], 1) && \
	!(bool->s_bool) && !(bool->d_bool))
		bool->e_bool = 0;
}

char	*skip_empty_blocks(char *input)
{
	t_pt	bool;
	int		i;
	int		j;

	i = 0;
	check_if_ended(&bool, 0);
	input = ft_strtrim(input, " \t");
	while (input[i])
	{
		if (((!bool.d_bool && !bool.s_bool && !bool.e_bool)) \
		&& (input[i] == 32 || input[i] == 9))
		{
			j = i - 1;
			while (input[++j] && (input[j] == 32 || input[j] == 9))
				;
			input = cut_string(input, i++, j);
		}
		else
			check_bool(input, i++, &bool); // Should check also for this
	}
	return (check_if_ended(&bool, 1), input);
}

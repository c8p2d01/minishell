/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_2_parse_input_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:21:12 by flormich          #+#    #+#             */
/*   Updated: 2021/12/26 16:02:51 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

int	parse_quote(t_struct *st, char *input, int i)
{
	if (input[i] == '\'')
		return (parse_simple_quote(st, input, i));
	return (parse_double_quote(st, input, i));
}

int	parse_double_quote(t_struct *st, char *input, int i)
{
	st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
	st->digit++;
	i++;
	while (input[i] != '"' || (input[i] == '"' && input[i - 1] == '\\'))
	{
		st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
		st->digit++;
		i++;
	}
	st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
	st->digit++;
	return (i + 1);
}

int	parse_simple_quote(t_struct *st, char *input, int i)
{
	st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
	st->digit++;
	i++;
	while (input[i] != '\'' && input[i] != '\0')
	{
		st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
		st->digit++;
		i++;
	}
	st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
	st->digit++;
	return (i + 1);
}

int	manage_parenthesis(t_struct *st, char *s, int i)
{
	int	n;

	n = 1;
	st->buf = add_char_to_buf(st, s[i]);
	while (s[i] && n > 0)
	{
		i++;
		st->buf = add_char_to_buf(st, s[i]);
		if (s[i] == '(')
			n++;
		else if (s[i] == ')')
			n--;
	}
	if (n > 0)
	{
		ft_putendl_fd("minishell: unclosed parenthesis", 2);
		return (-2);
	}
	return (i);
}

int	manage_separator(t_cmd *arr, char *s, int i)
{
	if (s[i] == '|')
	{
		if (s[i + 1] == '|')
		{
			arr->logical = 1;
			return (i + 2);
		}
		arr->logical = 0;
		return (i + 1);
	}
	else if (s[i] == '&' && s[i + 1] == '&')
	{
		arr->logical = 2;
		return (i + 2);
	}
	return (i + 1);
}

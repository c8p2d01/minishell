/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_manage_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:14:44 by flormich          #+#    #+#             */
/*   Updated: 2021/12/28 16:54:49 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	manage_doppel_quote(t_struct *st, char *str, int i, int test_quote)
{
	st->buf = add_char_to_buf(st, str[i++]);
	while (str[i] != '"' && str[i] != '\0')
	{
		if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0)
			|| (str[i] == '~' && is_expand_home(str[i + 1]) == 1)
			|| (str[i] == '$' && is_special_variable(str[i + 1]) == 1))
			i = launch_expand_variable(st, str, i) + 1;
		else
		{
			if (str[i] == '\\' && str[i + 1] == '"')
				st->buf = add_char_to_buf(st, str[i++]);
			st->buf = add_char_to_buf(st, str[i++]);
		}
	}
	if (str[i] == '"' || test_quote == 0)
	{
		if (str[i] == '"')
			st->buf = add_char_to_buf(st, '"');
		return (i);
	}
	ms_error_synthaxe('"');
	return (-2);
}

int	manage_simple_quote(t_struct *st, char *str, int i, int test_quote)
{
	st->buf = add_char_to_buf(st, str[i++]);
	while ((str[i] != '\'' && str[i] != '\0')
		|| (str[i] == ' ' && test_quote == 0))
		st->buf = add_char_to_buf(st, str[i++]);
	if (str[i] == '\'' || test_quote == 0)
	{
		if (str[i] == '\'')
			st->buf = add_char_to_buf(st, '\'');
		return (i);
	}
	ms_error_synthaxe('\'');
	return (-2);
}

int	launch_manage_quote(t_struct *st, char *str, int i, int test_quote)
{
	if (str[i] == '"')
		return (manage_doppel_quote(st, str, i, test_quote));
	return (manage_simple_quote(st, str, i, test_quote));
}

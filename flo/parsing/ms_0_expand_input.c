/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_0_expand_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:18:33 by flormich          #+#    #+#             */
/*   Updated: 2022/01/03 18:55:52 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	check_isvariable(t_struct *st, char *str, int i)
{
	if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0)
		|| (str[i] == '~' && is_expand_home(str[i + 1]) == 1)
		|| (str[i] == '$' && is_special_variable(str[i + 1]) == 1))
		return (1);
	return (0);
}

int	bufferize_input(t_struct *st, char *str, int i, int test_quote)
{
	while (str[i] != '\0' && i != -1)
	{
		if (test_quote == 1
			&& (i == 0 || (i > 0 && ft_isspace(str[i - 1]) == 1))
			&& check_is_wildcard(st, str, i) == 1)
			i = launch_expand_wildcard(st, str, i, i);
		else if (str[i] == '\\' && (str[i + 1] == '$' || str[i + 1] == '~'
				|| str[i + 1] == '"' || str[i + 1] == '\''))
			i = do_not_expand_variable(st, str, i);
		else if (check_isvariable(st, str, i) == 1)
			i = launch_expand_variable(st, str, i);
		else if (str[i] == '\'' || str[i] == '"')
			i = launch_manage_quote(st, str, i, test_quote);
		else
			i = launch_manage_pipe_parenthes(st, str, i, test_quote);
		i++;
	}
	if (st->nb_parenthesis != 0)
		ms_error_synthaxe('p');
	if (i == -1 || st->nb_parenthesis != 0)
		return (-1);
	st->buf = add_char_to_buf(st, '\0');
	return (0);
}

int	launch_expand_variable(t_struct *st, char *str, int i)
{
	if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0)
		|| (str[i] == '~' && is_expand_home(str[i + 1]) == 1))
		return (expand_variable(st, str, i));
	else if (str[i] == '$' && is_special_variable(str[i + 1]) == 1)
		return (expand_special_variable(st, str, i));
	return (expand_variable(st, str, i));
}

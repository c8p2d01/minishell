/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:01:48 by flormich          #+#    #+#             */
/*   Updated: 2021/12/23 19:26:45 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	manage_expand_variable(t_struct *st)
{
	int	i;

	i = 0;
	st->force_expand = -1;
	st->nb_cmd = 1;
	st->buf = ft_calloc(1, sizeof(char *));
	if (!st->buf)
		return (-1);
	while (ft_isspace(st->input[i]) == 1)
		i++;
	if (st->input[i] == '|' || st->input[i] == '&')
	{
		ms_error_synthaxe(st->input[i]);
		free(st->input);
		return (-1);
	}
	if (bufferize_input(st, st->input, i, 1) == -1)
	{
		free(st->buf);
		free(st->input);
		g_exit_value = 1;
		return (-1);
	}
	return (transfert_buf_input(st));
}

int	find_match(t_struct *st, int e, char *var, int pos)
{
	int	j;

	j = 0;
	while (st->env[e][j] == var[pos] && is_variable_end(st, var[pos] == 0))
	{
		if (st->env[e][j + 1] == '=' && is_variable_end(st, var[pos + 1]) == 1)
		{
			write_variable(st, e, j);
			return (pos);
		}
		pos++;
		j++;
	}
	return (0);
}

void	write_variable(t_struct *st, int e, int j)
{
	while (st->env[e][j + 2] != '\0')
	{
		st->buf = add_char_to_buf(st, st->env[e][j + 2]);
		j++;
	}
}

int	do_not_expand_variable(t_struct *st, char *str, int i)
{
	if (str[i + 1 == '"' || str[i + 1] == '\''])
		st->buf = add_char_to_buf(st, str[i]);
	st->buf = add_char_to_buf(st, str[i + 1]);
	return (i + 1);
}

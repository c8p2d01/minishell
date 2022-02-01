/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:14:36 by pnuti             #+#    #+#             */
/*   Updated: 2022/01/03 18:29:51 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	ms_run_env(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	if (arr->cmd[1])
	{
		write(2, "env: Unexpected argument\n", 26);
		return (127);
	}
	ms_env(st);
	return (0);
}

int	ms_run_export(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	int			n;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	n = 1;
	if (st->nb_cmd != 1 && if_run_export(st) == 0)
		return (0);
	while (arr->cmd[n])
	{
		if (ft_strchr(arr->cmd[n], '='))
		{
			if (ms_export(arr->cmd[n], st) != 0)
				return (1);
		}
		n++;
	}
	return (0);
}

//if (st->nb_cmd != 1 && ((!arr->logical && ((st->tr > 0
//&& !st->arr[st->tr - 1].logical) || st->tr == 0))))
int	ms_run_unset(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	int			n;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	n = 1;
	if (st->nb_cmd != 1 && if_run_unset(st) == 0)
		return (0);
	while (arr->cmd[n])
	{
		if (ms_unset(arr->cmd[n], st) != 0)
			return (1);
		n++;
	}
	return (0);
}

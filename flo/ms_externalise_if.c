/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_externalise_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 19:23:37 by flormich          #+#    #+#             */
/*   Updated: 2022/01/05 11:18:09 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	if_cd(t_struct *st)
{
	if (st->arr[st->tr].logical)
		return (0);
	if ((st->tr > 0 && !st->arr[st->tr - 1].logical) || st->tr == 0)
		return (1);
	return (0);
}

int	if_exit(t_struct *st)
{
	if (st->arr[st->tr].logical)
		return (0);
	if ((st->tr > 0 && !st->arr[st->tr - 1].logical) || st->tr == 0)
		return (1);
	return (0);
}

int	if_run_export(t_struct *st)
{
	if (st->arr[st->tr].logical)
		return (1);
	if ((st->tr > 0 && !st->arr[st->tr - 1].logical) || st->tr == 0)
		return (0);
	return (1);
}

int	if_run_unset(t_struct *st)
{
	if (st->arr[st->tr].logical)
		return (1);
	if (st->tr > 0 && !st->arr[st->tr - 1].logical)
		return (0);
	if (st->tr == 0)
		return (0);
	return (1);
}

int	if_launch_cmd(t_struct *st)
{
	if (st->tr == 0)
		return (1);
	if (st->arr[st->tr - 1].logical == 2 && g_exit_value == 0)
		return (1);
	if (st->arr[st->tr - 1].logical == 1 && g_exit_value > 0)
		return (1);
	if (!st->arr[st->tr - 1].logical)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:52:27 by flormich          #+#    #+#             */
/*   Updated: 2022/01/02 15:29:50 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

static void	set_red_one_cmd(t_struct *st, int which_cmd)
{
	if (st->arr[which_cmd].limiter != NULL)
		dup2(st->fd[READ], STDIN_FILENO);
	else
	{
		if (which_cmd == 0 || (which_cmd > 0
				&& st->arr[which_cmd - 1].logical != 0))
			dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
		else
			dup2(st->fd[READ], STDIN_FILENO);
	}
	dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
}

static void	set_red_first_cmd(t_struct *st, int which_cmd, int *next_fd)
{
	if (st->arr[which_cmd].limiter != NULL)
		dup2(st->fd[READ], STDIN_FILENO);
	else
		dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
	if (st->arr[which_cmd].fd_out != 1)
		dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
	else
		dup2(next_fd[WRITE], STDOUT_FILENO);
}

void	set_red_shell(t_struct *st, int which_cmd, int *next_fd)
{
	if (st->nb_cmd == 1 || st->arr[which_cmd].logical != 0)
		set_red_one_cmd(st, which_cmd);
	else if (which_cmd == 0)
		set_red_first_cmd(st, which_cmd, next_fd);
	else
	{
		dup2(st->fd[READ], STDIN_FILENO);
		if (which_cmd == st->nb_cmd - 1)
			dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
		else
			dup2(next_fd[WRITE], STDOUT_FILENO);
	}
	close(st->fd[READ]);
	close(st->fd[WRITE]);
}

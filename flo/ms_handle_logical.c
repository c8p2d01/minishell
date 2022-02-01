/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_logical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:42:06 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/29 19:14:18 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

static void	start_child(t_struct *st, t_cmd *a)
{
	char	*new_argv[4];

	new_argv[0] = st->argv[0];
	new_argv[1] = ft_strdup("-c");
	new_argv[2] = ft_substr(a->cmd[0],
			1, ft_revlen_until_char(a->cmd[0], ')') - 1);
	new_argv[3] = NULL;
	if (execve(ms_get_env(st->env, "SHELL"), new_argv, st->env) < 0)
		exit(1);
}

int	run_child(void *sst, void *cmd)
{
	t_struct	*st;
	t_cmd		*arr;
	int			pid;
	int			status;

	st = (t_struct *)sst;
	arr = (t_cmd *)cmd;
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		start_child(st, arr);
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		g_exit_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_value = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	return (0);
}

void	handle_logical(t_struct *st, int argc, char **argv)
{
	if (argc == 1)
		return ;
	else if (ft_strncmp(argv[1], "-c", 3) != 0)
	{
		ft_putendl_fd("cannot execute binary file", 2);
		exit(126);
	}
	st->input = ft_strdup(argv[2]);
	if (st->input && st->input[0] != '\0')
	{
		init_st(argc, argv, st);
		if (manage_expand_variable(st) == 0)
		{
			if (extract_cmd(st) == 0 && launch_cmd(st) != 0)
				g_exit_value = 1;
			free_memory(st);
		}
		init_st(argc, argv, st);
	}
	free_env(st);
}

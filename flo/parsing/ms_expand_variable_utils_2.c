/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:31:57 by flormich          #+#    #+#             */
/*   Updated: 2022/01/04 11:45:57 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static void	free_memory_wildcard(t_struct *st, struct dirent *dirp, DIR *dir)
{
	int	i;

	closedir(dir);
	free(dirp);
	if (st->wildcard_all == 0)
	{
		i = 0;
		while (i < st->nb_wildcard)
		{
			free(st->pat[i].pattern);
			i++;
		}
		free(st->pat);
	}
}

int	check_is_wildcard(t_struct *st, char *str, int i)
{
	int	wild_card;

	st->nb_wildcard = 1;
	wild_card = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) == 0
		&& str[i] != '$' && str[i] != '|')
	{
		if (str[i] == '"' || str[i] == '\'')
			return (0);
		if (str[i] == '*')
		{
			wild_card = 1;
			st->nb_wildcard++;
		}
		i++;
	}
	return (wild_card);
}

static int	find_wildcard_match(t_struct *st, struct dirent *d, int arg)
{
	char	*tmp;

	if (st->wildcard_all == 1)
		return (1);
	tmp = d->d_name;
	while (arg < st->nb_wildcard && st->pat[arg].pattern != NULL)
	{
		if (st->pat[arg].position == END)
			return (wildcard_match_end(st->pat[arg].pattern, tmp));
		st->digit = ft_strlen(st->pat[arg].pattern);
		if (st->pat[arg].position == BEGIN)
		{
			if (ft_strncmp(st->pat[arg].pattern, tmp, st->digit) != 0)
				return (0);
		}
		else
		{
			tmp = ft_strnstr(tmp, st->pat[arg].pattern, ft_strlen(tmp));
			if (tmp == NULL)
				return (0);
		}
		tmp += st->digit;
		arg++;
	}
	return (1);
}

int	launch_expand_wildcard(t_struct *st, char *str, int i, int i_org)
{
	DIR				*cur_dir;
	struct dirent	*dirp;

	st->is_wildcard_match = 0;
	st->include_hiddenfiles = check_include_hiddenfiles(str, i);
	i = launch_find_wc_pattern(st, str, i);
	if (i == -1)
		return (-1);
	cur_dir = opendir(ms_get_env(st->env, "PWD"));
	dirp = readdir(cur_dir);
	while (dirp != NULL)
	{
		if (dirp
			&& find_wildcard_match(st, dirp, 0) == 1
			&& (st->include_hiddenfiles != 0 || dirp->d_name[0] != '.'))
			cpy_match(st, dirp);
		dirp = readdir(cur_dir);
	}
	if (st->is_wildcard_match == 0)
		cpy_str_no_match(st, str, i_org);
	free_memory_wildcard(st, dirp, cur_dir);
	if (str[i] == '|' || str[i] == ')' || str[i] == '\0')
		return (i - 1);
	return (i);
}

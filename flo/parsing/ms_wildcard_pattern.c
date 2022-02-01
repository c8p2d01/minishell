/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:33:15 by flormich          #+#    #+#             */
/*   Updated: 2022/01/04 11:42:07 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	store_pattern(t_struct *st, char *str, int i, int len)
{
	if (i == 0 || ft_isspace(str[i - 1]) == 1)
		st->pat[st->arg].position = BEGIN;
	else
		st->pat[st->arg].position = MID;
	st->pat[st->arg].pattern = ft_substr(str, i, len);
	if (!st->pat[st->arg].pattern)
		return (-1);
	if (ft_isspace(str[i + len]) == 1 || str[i + len] == '\0'
		|| str[i + len] == '|')
	{
		st->pat[st->arg++].position = END;
		return (i + len);
	}
	st->arg++;
	return (i + len + 1);
}

static int	launch_store_pattern(t_struct *st, char *str, int i)
{
	int		len;

	while (str[i] == '*')
		i++;
	len = 0;
	while (str[i + len] != '*' && ft_isspace(str[i + len]) == 0
		&& is_wildcard_end(str[i + len]) == 0)
		len++;
	if (len > 0)
		return (store_pattern(st, str, i, len));
	return (i);
}

int	launch_find_wc_pattern(t_struct *st, char *str, int i)
{
	st->arg = 0;
	st->wildcard_all = 0;
	if (ft_isspace(str[i + 1]) == 1 || is_wildcard_end(str[i + 1]) == 1)
	{
		st->wildcard_all = 1;
		return (i + 1);
	}
	while (str[i] == '*')
		i++;
	st->pat = malloc((st->nb_wildcard) * sizeof(t_pat));
	if (!st->pat)
		return (-1);
	while (i != -1 && ft_isspace(str[i]) == 0
		&& st->arg < st->nb_wildcard + 1 && is_wildcard_end(str[i]) == 0)
		i = launch_store_pattern(st, str, i);
	st->nb_wildcard = st->arg;
	return (i);
}

void	cpy_str_no_match(t_struct *st, char *str, int i_org)
{
	while (str[i_org] != '\0'
		&& ft_isspace(str[i_org]) == 0 && is_wildcard_end(str[i_org]) == 0)
	{
		st->buf = add_char_to_buf(st, str[i_org]);
		i_org++;
	}
}

void	cpy_match(t_struct *st, struct dirent *dirp)
{
	int	j;

	j = 0;
	while (dirp->d_name[j])
		st->buf = add_char_to_buf(st, dirp->d_name[j++]);
	st->buf = add_char_to_buf(st, ' ');
	st->is_wildcard_match = 1;
}

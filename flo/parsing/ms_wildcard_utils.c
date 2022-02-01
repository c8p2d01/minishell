/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:56:35 by flormich          #+#    #+#             */
/*   Updated: 2021/12/21 18:36:36 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	check_include_hiddenfiles(const char *str, const int i)
{
	int		j;
	int		mouch_a;
	int		mouch_minus;

	mouch_a = 0;
	mouch_minus = 0;
	j = -1;
	while (ft_isspace(str[i + j]) != 0 && str[i + j] != '|' && i + j > 0)
		j--;
	while (ft_isspace(str[i + j]) == 0 && str[i + j] != '|' && i + j > 0)
	{
		if (str[i + j] == 'a')
			mouch_a = 1;
		if (str[i + j] == '-')
			mouch_minus = 1;
		j--;
	}
	while (ft_isspace(str[i + j]) == 1)
		j--;
	if (str[i + j] != 's' || str[i + j - 1] != 'l')
		mouch_a = 0;
	if (mouch_a == 1 && mouch_minus == 1)
		return (1);
	return (0);
}

int	wildcard_match_end(char *pat, char *dir)
{
	int		len_pat;
	int		len_dir;

	len_pat = ft_strlen(pat);
	len_dir = ft_strlen(dir);
	if (len_pat > len_dir)
		return (0);
	while (len_pat > 0)
	{
		if (pat[len_pat - 1] == dir[len_dir - 1])
		{
			len_pat--;
			len_dir--;
		}
		else
			return (0);
	}
	return (1);
}

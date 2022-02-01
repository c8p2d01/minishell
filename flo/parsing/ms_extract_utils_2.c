/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:08:00 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/23 19:28:48 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	skip_parenthesis(char *s, int i, int max)
{
	int	n;

	n = 1;
	while (s[i] && n > 0 && i < max)
	{
		if (s[i] == '(')
			n++;
		else if (s[i] == ')')
			n--;
		i++;
	}
	return (i);
}

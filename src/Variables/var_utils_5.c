/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:31:22 by gwen              #+#    #+#             */
/*   Updated: 2026/03/20 13:15:59 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_quote(char *src)
{
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	while (*src)
	{
		if (*src == '\'' && !dq)
			sq = !sq;
		else if (*src == '"' && !sq)
			dq = !dq;
		else if (*src == ' ' && !dq && !sq)
			return (1);
		src++;
	}
	return (0);
}

static int	add_splitted_to_cmd(t_cmd *cmd, int i, char **words)
{
	int	count;
	int	j;

	j = 0;
	while (words[j])
		j++;
	count = j;
	free(cmd->av[i]);
	cmd->av[i] = ft_strdup(words[0]);
	if (cmd->av[i])
		return (0);
	j = 1;
	while (words[j])
	{
		if (!add_arg_to_cmd(words[j], cmd))
			return (0);
		j++;
	}
	return (count);
}

void	word_split(t_cmd *cmd, int *i)
{
	char	**words;
	int		count;

	if (!has_quote(cmd->av[*i]))
		return ;
	words = ft_split(cmd->av[*i], ' ');
	if (!words)
		return ;
	count = add_splitted_to_cmd(cmd, *i, words);
	free_tab(words);
	if (count > 0)
		*i += count - 1;
}

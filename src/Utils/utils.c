/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:08:54 by gwen              #+#    #+#             */
/*   Updated: 2026/02/12 21:15:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	free_data(t_data data)
{
	free(data->line);
	free(data->infile);
	free(data->outfile);
	error_cleanup(data->token);
	free(data);
}

void	fill_args(char *args, t_token *token)
{
	int		i;
	t_token	*tmp;
	
	i = 0;
	tmp = token;
	while (tmp->type == WORD)
	{
		args[i] = malloc(sizeof(char) * ft_strlen(tmp->value));
		if (!args[i])
			return (perror(malloc), NULL);
		args[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
}

char	**get_args(t_token *token)
{
	int		i;
	char	**args;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	if (i == 1)
		return(ft_split(token->value));
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (perror(malloc), NULL);
	args[i] = '\0';
	return (args);
}

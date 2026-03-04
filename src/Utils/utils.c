/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:08:54 by gwen              #+#    #+#             */
/*   Updated: 2026/03/04 11:35:33 by storck           ###   ########.fr       */
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

int	is_redir(t_type type)
{
	if (type == INPUT || type == APPEND
		|| type == OUTPUT || type == HEREDOC)
		return (1);
	return (0);
}

int	is_number(char *num)
{
	int	n;

	n = ft_atoi(num);
	if (n != 0)
		return (1);
	else if (ft_isdigit(num[0]) && num[0] == '0')
		return (1);
	else
		return (0);
}

//Select all the lines you want and CTRL+K+U to uncomment and CTRL+K+C to comment

// void	fill_args(char *args, t_token *token)
// {
// 	int		i;
// 	t_token	*tmp;
	
// 	i = 0;
// 	tmp = token;
// 	while (tmp->type == WORD)
// 	{
// 		args[i] = malloc(sizeof(char) * ft_strlen(tmp->value));
// 		if (!args[i])
// 			return (perror(malloc), NULL);
// 		args[i] = ft_strdup(tmp->value);
// 		i++;
// 		tmp = tmp->next;
// 	}
// }

// char	**get_args(t_token *token)
// {
// 	int		i;
// 	char	**args;
// 	t_token *tmp;

// 	i = 0;
// 	tmp = token;
// 	while (tmp->type == WORD)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	if (i == 1)
// 		return (ft_split(token->value));
// 	args = malloc(sizeof(char *) * (i + 1));
// 	if (!args)
// 		return (perror(malloc), NULL);
// 	args[i] = '\0';
// 	return (args);
// }

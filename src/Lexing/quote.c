/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:53:33 by gwen              #+#    #+#             */
/*   Updated: 2026/02/16 11:53:34 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quote(char c, t_quote *quote)
{
	if (c == '\'' && !quote->dq)
		quote->sq = !quote->sq;
	else if (c == '"' && !quote->sq)
		quote->dq = !quote->dq;
}

char	*ft_incremente(char *line, char *buf, int *i, t_quote *quote)
{
	int	j;

	j = 0;
	while (line[*i])
	{
		if ((line[*i] == '\'' && !quote->dq)
			|| (line[*i] == '"' && !quote->sq))
			handle_quote(line[*i], quote);
		else if (!quote->sq && !quote->dq
			&& (is_space(line[*i]) || is_operator(line[*i])))
			break ;
		buf[j++] = line[(*i)++];
	}
	if (quote->sq || quote->dq)
		return (free(buf), NULL);
	buf[j] = 0;
	return (buf);
}

char	*read_word(char *line, int *i)
{
	char	*buf;
	t_quote	quote;

	quote.sq = 0;
	quote.dq = 0;
	buf = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!buf)
		return (NULL);
	if (ft_incremente(line, buf, i, &quote) == NULL)
		return (NULL);
	return (buf);
}

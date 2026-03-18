/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:43:38 by storck            #+#    #+#             */
/*   Updated: 2026/03/18 12:04:10 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_cleanup_lexing(t_token *tokens, int status, t_data *data)
{
	clean_tokens(tokens);
	if (status == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
	else if (status == 0)
	{
		ft_putstr_fd("minishell: syntax error: unexpected", STDERR_FILENO);
		ft_putstr_fd(" EOF while looking for matching quote\n", STDERR_FILENO);
	}
	data->exit_code = 2;
}

void	error_cleanup_parsing(t_cmd *cmds, const char *error, t_token *token,
			t_data *data)
{
	(void)token;
	if (cmds)
		free_cmds(cmds);
	if (error)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '",
			STDERR_FILENO);
		ft_putstr_fd((char *)error, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	data->exit_code = 2;
}

void	error_command_not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	error_permission_denied(const char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)file, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

void	error_no_such_file(const char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

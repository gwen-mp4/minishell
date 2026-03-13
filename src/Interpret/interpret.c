/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:43:54 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 12:33:32 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static void	wait_all(pid_t	*pids, int total, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < total)
	{
		waitpid(pids[i], &status, 0);
		if (i == total - 1)
			data->exit_code = get_exit_code(status);
		i++;
	}
}

static pid_t	*run_pipes(t_cmd **cmd, t_data *data, int total)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * total);
	if (!pids)
		return (NULL);
	i = 0;
	while (data->pipe_count > 0)
	{
		do_pipe(*cmd, data, pids, i++);
		data->pipe_count--;
		*cmd = (*cmd)->next;
	}
	return (pids);
}

static void	exec_last(t_cmd *cmd, t_data *data, int save_in, int save_out)
{
	pid_t	*pids;
	int		total;

	total = data->pipe_count + 1;
	pids = run_pipes(&cmd, data, total);
	if (!pids)
	{
		close(save_in);
		close(save_out);
		return ;
	}
	pids[total - 1] = fork_process();
	if (!pids[total - 1])
		find_way(cmd, data, pids);
	redirect_fd(save_in, STDIN_FILENO);
	redirect_fd(save_out, STDOUT_FILENO);
	wait_all(pids, total, data);
	setup_signal();
	free(pids);
}

void	execution(t_cmd *cmd, t_data *data)
{
	int		save_in;
	int		save_out;

	if (!cmd)
		return ;
	save_in = dup_process(STDIN_FILENO, -1);
	save_out = dup_process(STDOUT_FILENO, save_in);
	if (prepare_heredoc(cmd) == EXIT_FAILURE || !cmd->av || !cmd->av[0])
	{
		close(save_in);
		close(save_out);
		return ;
	}
	if (data->pipe_count == 0 && is_builtin(cmd->av[0]))
	{
		exec_builtin(cmd, cmd->av, data);
		redirect_fd(save_in, STDIN_FILENO);
		redirect_fd(save_out, STDOUT_FILENO);
		return ;
	}
	exec_last(cmd, data, save_in, save_out);
}

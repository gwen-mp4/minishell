/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:43:54 by storck            #+#    #+#             */
/*   Updated: 2026/03/10 13:17:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd->av || !cmd->av[0])
		exit (0);
	signal_child();
	set_fds(cmd);
	path = get_path(cmd->av[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd->av[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (execve(path, cmd->av, env) == -1)
	{
		perror(cmd->av[0]);
		exit(1);
	}
}

void	do_pipe(t_cmd *cmd, t_data *data, pid_t *pids, int index)
{
	int		p_fd[2];

	pipe_process(p_fd);
	pids[index] = fork_process();
	if (!pids[index])
	{
		close(p_fd[0]);
		redirect_fd(p_fd[1], STDOUT_FILENO);
		find_way(cmd, data->env, data);
	}
	else
	{
		close(p_fd[1]);
		redirect_fd(p_fd[0], STDIN_FILENO);
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
	int		i;

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
		find_way(cmd, data->env, data);
	redirect_fd(save_in, STDIN_FILENO);
	redirect_fd(save_out, STDIN_FILENO);
	i = 0;
	while (i < total)
		waitpid(pids[i++], NULL, 0);
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
		redirect_fd(save_out, STDIN_FILENO);
		return ;
	}
	exec_last(cmd, data, save_in, save_out);
}

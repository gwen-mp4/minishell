/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:27:33 by storck            #+#    #+#             */
/*   Updated: 2026/03/19 12:04:40 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_pipe(t_cmd *cmd, t_data *data, pid_t *pids, int index)
{
	int		p_fd[2];

	pipe_process(p_fd);
	pids[index] = fork_process();
	if (!pids[index])
	{
		close(p_fd[0]);
		redirect_fd(p_fd[1], STDOUT_FILENO);
		find_way(cmd, data, pids);
	}
	else
	{
		close(p_fd[1]);
		redirect_fd(p_fd[0], STDIN_FILENO);
	}
}

void	redirect_fd(int old_fd, int new_fd)
{
	if (old_fd == new_fd)
		return ;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(old_fd);
}

int	file_read_process(char *infile)
{
	int	fd_in;

	if (opendir(infile) != NULL)
	{
		if (errno == ENOENT)
			return (0);
	}
	fd_in = open(infile, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		ft_putstr_fd("open ", 2);
		perror(infile);
		return (-1);
	}
	return (fd_in);
}

int	file_write_process(char *outfile)
{
	int	fd_out;

	if (opendir(outfile) == NULL)
		return (error_is_a_directory(outfile), -1);
	fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("open ", 2);
		perror(outfile);
		return (-1);
	}
	return (fd_out);
}

void	free_find_way(t_data *data, pid_t *pids, t_cmd *cmd)
{
	if (cmd != NULL)
		set_fds(cmd);
	close_all(data->fd_in, data->fd_out);
	free_data(data);
	free(pids);
}

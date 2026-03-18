/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:27:33 by storck            #+#    #+#             */
/*   Updated: 2026/03/18 13:10:32 by gwen             ###   ########.fr       */
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

	fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("open ", 2);
		perror(outfile);
		return (-1);
	}
	return (fd_out);
}

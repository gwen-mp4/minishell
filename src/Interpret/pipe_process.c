/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:27:33 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 15:27:36 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	pipe_process(int p_fd[2])
{
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	redirect_fd(int old_fd, int new_fd)
{
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

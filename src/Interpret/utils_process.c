/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:54:49 by storck            #+#    #+#             */
/*   Updated: 2026/03/11 09:54:49 by storck           ###   ########.fr       */
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
		exit (1);
	}
	return (pid);
}

void	pipe_process(int p_fd[2])
{
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
}

int	dup_process(int fd, int save_in)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		if (save_in != -1)
			close(save_in);
		perror("dup");
		exit (1);
	}
	return (new_fd);
}

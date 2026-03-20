/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_file_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:01:44 by storck            #+#    #+#             */
/*   Updated: 2026/03/20 13:56:28 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit_1(t_data *data)
{
	data->exit_code = 1;
}

int	file_append_process(char *outfile)
{
	int	fd_out;
	DIR	*fd;

	fd = opendir(outfile);
	if (fd != NULL)
		return (error_is_a_directory(outfile), closedir(fd), -1);
	fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(outfile);
		return (-1);
	}
	return (fd_out);
}

void	free_heredoc(char *line, int fd, t_data *data, char *doc_name)
{
	free(line);
	close (fd);
	rl_clear_history();
	free(doc_name);
	free_data(data);
}

void	check_find_way(t_data *data, t_cmd *cmd, pid_t *pids)
{
	if (!cmd->av || !cmd->av[0])
	{
		free_find_way(data, pids, cmd);
		exit(0);
	}
	if (set_fds(cmd) == EXIT_FAILURE)
	{
		free_find_way(data, pids, NULL);
		exit(1);
	}
}

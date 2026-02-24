/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:42 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 12:00:46 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		free(tabl[i++]);
	free(tabl);
}

char	**paths(char **envp)
{
	char	**my_paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			path = envp[i] + 5;
		i++;
	}
	if (!path)
		return (NULL);
	my_paths = path_split(path, ':');
	return (my_paths);
}

char	*build_my_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	if (!full_path)
		return (free(tmp), NULL);
	free(tmp);
	return (full_path);
}

char	*get_path(char *cmd, char **envp)
{
	char	**my_paths;
	char	*good_path;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": no such file or directory", 2);
		return (0);
	}
	i = -1;
	my_paths = paths(envp);
	while (my_paths[++i])
	{
		good_path = build_my_path(my_paths[i], cmd);
		if (good_path && access(good_path, X_OK) == 0)
			return (free_tab(my_paths), good_path);
		free(good_path);
	}
	return (free_tab(my_paths), NULL);
}

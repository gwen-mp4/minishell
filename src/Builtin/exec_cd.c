/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:02:03 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 14:00:56 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	update_oldpwd(t_data *data)
{
	t_list	*tmp;
	char	*test;
	int		len;

	tmp = data->envlst;
	test = NULL;
	len = len_list(tmp);
	while (len--)
	{
		if (!ft_strncmp(tmp->str, "PWD=", 4))
			test = tmp->str;
		tmp = tmp->next;
	}
	if (!test)
		export_ex("OLDPWD", &data->envlst);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (perror("malloc"));
		unset("OLDPWD", &data->envlst);
		export_ex(test, &data->envlst);
	}
	free(test);
}

static void	update_pwd(t_data *data, char *arg)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(arg);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (perror("malloc"));
	unset("PWD", &data->envlst);
	export_ex(pwd, &data->envlst);
	free(pwd);
}

char	*get_home(t_list *env)
{
	t_list	*tmp;

	tmp = env->next;
	while (tmp != env)
	{
		if (!ft_strncmp(tmp->str, "HOME=", 5))
			return (&(tmp->str[5]));
		tmp = tmp->next;
	}
	return (NULL);
}

int	exec_cd(t_data *data, char **args)
{
	char	*path;

	if (count_arg(args) > 2)
		return (error_too_many_arguments(args[0]), 1);
	if (count_arg(args) == 1)
		path = get_home(data->envlst);
	else
		path = args[1];
	if (!path)
		return (ft_putendl_fd("cd: HOME not set", 2), 1);
	if (chdir(path) == -1)
	{
		if (errno == EACCES)
			error_permission_denied(path);
		else
			error_no_such_file(path);
		return (1);
	}
	update_pwd(data, path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:02:03 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 12:59:02 by storck           ###   ########.fr       */
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

int	exec_cd(t_data *data, char **args)
{
	int	res;

	if (count_arg(args) == 2)
	{
		res = chdir(args[1]);
		if (res == 0)
			update_pwd(data, args[1]);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(args[1]);
		return (res);
	}
	else if (count_arg(args) > 2)
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
	return (1);
}

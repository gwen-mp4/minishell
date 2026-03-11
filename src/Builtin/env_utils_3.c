/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:22:39 by storck            #+#    #+#             */
/*   Updated: 2026/03/11 09:53:06 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_list(t_list *lst)
{
	t_list	*tmp;
	int		i;

	if (!lst)
		return (0);
	i = 1;
	tmp = lst->next;
	if (!tmp)
		return (1);
	while (tmp != lst)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	sort_array(char **arr, int len)
{
	int		i;
	int		j;
	int		diff;
	char	*temp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], ft_strlen(arr[i]));
			if (diff > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				continue ;
			}
			j++;
		}
		i++;
	}
}

char	**lst_to_arr(t_list *env)
{
	t_list	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = lst->str;
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = lst->str;
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

bool	null_env(t_data *data)
{
	char	path[PATH_MAX];
	char	*tmp;
	int		ex;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !append(&(data->envlst), tmp)
		|| getcwd(path, PATH_MAX) == NULL)
	{
		ex = data->exit_code;
		free_data(data);
		exit(ex);
	}
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !append(&(data->envlst), tmp))
	{
		ex = data->exit_code;
		free_data(data);
		exit(ex);
	}
	return (1);
}

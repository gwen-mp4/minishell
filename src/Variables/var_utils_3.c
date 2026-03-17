//42 HEADER

#include "../../includes/minishell.h"

static void	fill_buf(char *src, char *dest)
{
	int	i;
	int	j;
	int	dq;
	int	sq;

	i = 0;
	j = 0;
	dq = 0;
	sq = 0;
	while (src[i])
	{
		if (src[i] == '\'' && !dq)
			sq = !sq;
		else if (src[i] == '"' && !sq)
			dq = !dq;
		else
			dest[j++] = src[i];
		i++;
	}
	dest[j] = 0;
}

/*Function that will strip all quotes*/
void	strip_quotes(char **str)
{
	char	*buf;

	if (!str || !*str)
		return ;
	buf = malloc(ft_strlen(*str) + 1);
	if (!buf)
		return ;
	fill_buf(*str, buf);
	free(*str);
	*str = buf;
}

int	var_declaration(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	new_var(t_data *data, char *str)
{
	char	*var_name;
	char	*var_content;
	int		i;

	var_name = malloc(sizeof(char));
	if (!var_name)
		return ;
	var_content = malloc(sizeof(char));
	if (!var_content)
		return ;
	i = var_declaration(str);
	memmove(var_name, str, i);
	memmove(var_content, &str[i + 1], ft_strlen(str) - (i));
	var_name[i] = 0;
	var_content[ft_strlen(str) - i] = 0;
	add_var(data, var_name, var_content);
}

void	pull_back_av(char **av)
{
	int	i;

	free(av[0]);
	av[0] = NULL;
	i = 1;
	while (av[i])
	{
		av[i - 1] = av[i];
		i++;
	}
	av[i - 1] = NULL;
}

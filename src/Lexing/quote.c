//Put 42 header

#include "../../includes/minishell.h"

/*Function that will read between quote and return an allocaed dest containing word with ft_substr*/
char	*read_word(char *line, int *i)
{
	int	start;
	int	sq;
	int	dq;

	start = *i;
	sq = 0;
	dq = 0;
    while (line[*i])
	{
        if (line[*i] == '\'' && !dq)
            sq = !sq;
        else if (line[*i] == '"' && !sq)
            dq = !dq;
        else if (!sq && !dq)
		{
            if (is_space(line[*i]) || is_special(line[*i]))
                break;
        }
        (*i)++;
    }
    if (sq || dq)
        return (NULL);
    return (ft_substr(line, start, *i - start));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:18:46 by gwen              #+#    #+#             */
/*   Updated: 2026/03/09 12:15:39 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*dest;

	dest = ft_calloc(1, sizeof(t_list));
	if (!dest)
		return (NULL);
	dest->str = content;
	dest->next = NULL;
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
    t_list  *n = ft_lstnew("Hello");
    if (n)
    {
        printf("Node cree: %s\n", (char *)n->content);
        printf("Next: %p\n", (void *)n->next);
        free(n);
    }
    else
        printf("Erreur\n");

    return (0);
}
*/

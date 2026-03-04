/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:18:46 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 15:18:59 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*dest;

	dest = ft_calloc(1, sizeof(t_list));
	if (!dest)
		return (NULL);
	dest->content = content;
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

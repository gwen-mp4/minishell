/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:09:02 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 16:09:07 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*head = NULL;
	t_list	*n1 = ft_lstnew("A");
	t_list	*n2 = ft_lstnew("B");

	ft_lstadd_front(&head, n1);
	ft_lstadd_front(&head, n2);

	t_list	*tmp = head;
	while (tmp)
	{
		printf("%s -> ", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("NULL\n");

	free(n1);
	free(n2);

	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:35:18 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 16:35:20 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		i;
	t_list	*tmp_lst;

	if (lst)
	{
		i = 0;
		tmp_lst = lst;
		while (tmp_lst->next)
		{
			tmp_lst = tmp_lst->next;
			i++;
		}
		return (tmp_lst);
	}
	else
		return (0);
}
/*
#include <stdio.h>
#include <string.h>

void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*head = ft_lstnew(strdup("A"));
	head->next = ft_lstnew(strdup("B"));
	head->next->next = ft_lstnew(strdup("C"));

	t_list	*last = ft_lstlast(head);
	if (last)
		printf("Last node: %s\n", (char *)last->content);
	ft_lstclear(&head, del);

	return (0);
}
	*/

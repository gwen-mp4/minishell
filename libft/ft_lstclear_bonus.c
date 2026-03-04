/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:02:48 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 17:02:49 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_list;
	t_list	*tmp_nextlist;

	if (!lst || !del)
		return ;
	tmp_list = *lst;
	while (tmp_list)
	{
		tmp_nextlist = tmp_list->next;
		ft_lstdelone(tmp_list, del);
		tmp_list = tmp_nextlist;
	}
	*lst = NULL;
}
/*
#include <stdio.h>
#include <stdlib.h>
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

	ft_lstclear(&head, del);

	if (head == NULL)
		printf("Les nodes ont ete clear\n");
	else
		printf("Non\n");
	return (0);
}
*/

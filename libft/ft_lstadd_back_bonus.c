/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:39:05 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 16:39:06 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list->next)
		list = list->next;
	list->next = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*head = NULL;

	ft_lstadd_back(&head, ft_lstnew("A"));
	ft_lstadd_back(&head, ft_lstnew("B"));
	ft_lstadd_back(&head, ft_lstnew("C"));

	t_list	*tmp = head;
	while (tmp)
	{
		printf("%s -> ", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("NULL\n");

	t_list	*tmp2;
	while (head)
	{
		tmp2 = head->next;
		free(head);
		head = tmp2;
	}
	return (0);
}
	*/

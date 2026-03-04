/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:10:20 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 17:10:21 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp_list;

	if (!lst || !f)
		return ;
	tmp_list = lst;
	while (tmp_list)
	{
		(*f)(tmp_list->content);
		tmp_list = tmp_list->next;
	}
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*f(void *content)
{
	char	*str = (char *)content;
	char	*res = malloc(strlen(str) + 1);
	strcpy(res, str);
	for (int i = 0; res[i]; i++)
		res[i] = ft_toupper(res[i]);
	return (res);
}

int	main(void)
{
	t_list	*head = NULL;

	ft_lstadd_back(&head, ft_lstnew(("A")));
	ft_lstadd_back(&head, ft_lstnew(("b")));
	ft_lstadd_back(&head, ft_lstnew(("c")));

	t_list	*tmp = head;
	while (tmp)
	{
		printf("%s -> ", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("NULL\n");

	return (0);
}
*/

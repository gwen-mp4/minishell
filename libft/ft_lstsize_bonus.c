/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:22:21 by gwen              #+#    #+#             */
/*   Updated: 2025/11/12 16:22:22 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp_lst;

	if (lst)
	{
		i = 1;
		tmp_lst = lst;
		while (tmp_lst->next)
		{
			tmp_lst = tmp_lst->next;
			i++;
		}
		return (i);
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

	printf("Taille de la liste: %d\n", ft_lstsize(head));
	ft_lstclear(&head, del);

	return (0);
}
	*/

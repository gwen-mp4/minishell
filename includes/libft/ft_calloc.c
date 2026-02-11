/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:07:00 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:37:37 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mempt;

	mempt = malloc(nmemb * size);
	if (!mempt)
		return (0);
	ft_bzero(mempt, nmemb * size);
	return (mempt);
}
/*
#include <stdio.h>

int main() {
    int *ptr = (int *)ft_calloc(4294967295, sizeof(int));
    
    // Checking if failed or pass
    if (ptr == NULL) {
        printf("Allocation Failed");
        exit(0);
    }
    
    // No need to populate as already
    // initialized to 0
        
    // Print the array
    for (int i = 0; i < 5; i++)
        printf("%d ", ptr[i]);
    return 0;
}
*/

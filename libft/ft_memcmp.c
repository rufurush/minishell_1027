/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:53:22 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:35:09 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t i;
    const unsigned char *t1 = (const unsigned char *)s1;
    const unsigned char *t2 = (const unsigned char *)s2;
    
    i = 0;
    while (i < n)
    {
        if (t1[i] != t2[i])
            return (t1[i] - t2[i]);
        i++;
    }
    return(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:01:33 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:34:48 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memchr(const void *s, int c, size_t n)
{
    size_t i;
    i = 0;
    const unsigned char *ptr = (const unsigned char *)s;
    
    while(i < n)
    {
        if(ptr[i] == (unsigned char)c)
        {
            //return((void *)(const unsigned char *)ptr + i);
            return((void *)(ptr + i));
        }
        i++;
    }
    return(NULL);
}

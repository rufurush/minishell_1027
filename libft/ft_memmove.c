/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:31 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:35:48 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void    *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i;
    
    if(dest == src || !n)
    {
        return(dest);
    }
    i = 0;
    if(dest < src)
    {
        while(i < n)
        {
            *((char *)dest + i) = *((char *)src + i);
            i++;
        }
    }
    else
    {
        while(n > 0)
        {
            *((char *)dest + n - 1) = *((char *)src + n - 1);
            n--;
        }
    }
    return(dest);
}

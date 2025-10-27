/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:35:39 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:35:31 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void     *ft_memcpy(void  *restrict dst, const void *restrict src, size_t n)
{
    size_t i;
    i = 0;
    while(i < n)
    {
        *((unsigned char *)dst + i) = *((unsigned char *)src + i);
        i++;
    }
    return(dst);
}

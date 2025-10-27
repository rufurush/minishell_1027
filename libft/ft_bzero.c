/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:46:56 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:31:54 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_bzero(void   *s, size_t n)
{
    size_t i;
    i = 0;
    while(n > i)
    {
        *((unsigned char *)s + i) = 0;
        i++;
    }
}

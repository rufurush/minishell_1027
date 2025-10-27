/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:11:50 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:44:12 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "libft.h"
int ft_tolower(int c)
{
    if((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')
    {
        c += 32;
    }
    return(c);
}

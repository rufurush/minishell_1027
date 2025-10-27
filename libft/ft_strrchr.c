/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:42:08 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:41:47 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char      *ft_strrchr(const char *s, int c)
{
    int len;

    len = ft_strlen(s);    
    if(c == '\0')
        return((char *)s + len);
    while(len >= 0)
    {
        if(s[len] == c)
            return((char *)(s + len));
        len--;
    }
    return(NULL);
}

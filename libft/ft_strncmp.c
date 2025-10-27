/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:02:32 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:39:51 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    i = 0;
    if(n == 0)
        return(0);
    while(s1[i] != '\0' && s2[i] != '\0' && i < n && s1[i] == s2[i])
        i++;
    if(i == n)
        return(0);
    return(s1[i] - s2[i]);
}

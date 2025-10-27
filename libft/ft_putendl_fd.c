/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:28:24 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:36:25 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_putendl_fd(char *s, int fd)
{
    int i;
    i = 0;
    while(s[i] != '\0')
    {
        write(fd, &s[i], 1);
        i++;
    }
    write(fd, "\n", 1);
}

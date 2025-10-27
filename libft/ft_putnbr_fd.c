/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:35:46 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:52:02 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_putnbr_fd(int n, int fd)
{
    if(n == -2147483648)
    {
        ft_putchar_fd('-', fd);
        ft_putchar_fd('2', fd);
        ft_putnbr_fd(147483648, fd);
    }
    else if(n < 0)
    {
        ft_putchar_fd('-',  fd);
        n = -n;
        ft_putnbr_fd(n, fd);
    }
    else if(n > 9)
    {
        ft_putnbr_fd(n / 10, fd);
        ft_putchar_fd(n % 10 + '0', fd);
    }
    else
        ft_putchar_fd(n + '0', fd);
}

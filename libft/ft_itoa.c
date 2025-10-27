/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:58:25 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:34:19 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static  int   digit_count(int n)
{
    int len;
    len = 0;
    if(n <= 0)
        len = 1;
    while(n != 0)
    {
        n /= 10;
        len++;
    }
    return(len);
}

static  void    fill_number(char *nbr, int n, int len)
{
    nbr[len] = '\0';
    if(n == 0)
        nbr[0] = '0';
    while(n > 0)
    {
        nbr[--len] = (n % 10) + '0';
        n /= 10;
    }
}

char    *ft_itoa(int n)
{
    char    *nbr;
    int     len;

    if(n == -2147483648)
        return(ft_strdup("-2147483648"));
    len = digit_count(n);
    nbr = (char *)malloc(sizeof(char) * (len + 1));
    if(!nbr)
        return(NULL);
    if(n < 0)
    {
        nbr[0] = '-';
        n = -n;
        fill_number(nbr + 1, n, len - 1);
    }
    else
        fill_number(nbr, n, len);
    return(nbr);
}
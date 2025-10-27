/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:27:26 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:36:46 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t i;
	if(s == NULL)
		return;
	i = 0;
	while(s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

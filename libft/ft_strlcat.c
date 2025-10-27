/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:34:54 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:22:04 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int dst_len;
	unsigned int src_len;
	unsigned int rest_len;
	unsigned int i;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);

	if(size < dst_len)
		return(size + src_len);
	rest_len = size - dst_len - 1;
	i = 0;
	while(i < rest_len)
	{
		if(src[i] == '\0')
			break;
		dest[dst_len + i] = src[i];
		i++;
	}
	dest[dst_len] = '\0';
	return(src_len + dst_len);
}


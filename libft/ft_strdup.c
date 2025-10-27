/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:14:23 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 18:56:28 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int i;
	int len;
	char *s2;

	len = 0;

	while(s1[len] != '\0')
		len++;
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if(!s2)
		return(NULL);
	while(s1[i] !='\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return(s2);
}

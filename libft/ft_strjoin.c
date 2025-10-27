/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:57:24 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 18:57:26 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t i;
	size_t j;
	char *result;

	if(!s1 || !s2)
		return(NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if(!result)
		return(NULL);
	i = 0;
	while(i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while(j < ft_strlen(s2))
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return(result);
}
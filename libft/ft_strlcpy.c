/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:28:47 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:38:35 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


size_t	ft_strlcpy(char *restrict dst, const char * restrict src, size_t dstsize)
{
	size_t i;
	size_t src_len;

	i = 0;
	src_len = ft_strlen(src);

	if(dstsize == 0)//strlcpyはdstがdstsizeより小さい場合を考慮しなくて良い。なぜならユーザー側に対して
	//ちゃんとdstsize 分だけメモリを確保しといてね！」という前提の上で動く関数だから。つまり自分でmain関数で設定する。
	{
		return(src_len);//srclenを返してあげることで本来入れるべきだった長さの物を返す
	}
	while(src[i] !='\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return(src_len);
}

// int main()
// {
// 	char dest[20];
// 	char *src = "HelloWorld!";
// 	size_t len = 10;

// 	size_t result = ft_strlcpy(dest, src, len);

// 	printf("%zu", result);
// }
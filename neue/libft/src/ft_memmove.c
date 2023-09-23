/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:00:07 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	if (dest == src || n == 0)
		return (dest);
	else if (dest > src && dest <= (src + n))
	{
		dest += n;
		src += n;
		while (i > 0)
		{
			dest--;
			src--;
			*(unsigned char *)dest = *(unsigned char *)src;
			i--;
		}
	}
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}

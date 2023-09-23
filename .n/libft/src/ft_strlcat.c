/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:41:37 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	i;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (!size)
		return (lsrc);
	if (size < ldst)
		return (size + lsrc);
	i = 0;
	while (src[i] && (ldst + i) < (size - 1))
	{
		dst[i + ldst] = src[i];
		i++;
	}
	dst[i + ldst] = '\0';
	return (ldst + lsrc);
}

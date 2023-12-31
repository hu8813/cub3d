/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:13:43 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/24 21:37:27 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		strsize;

	if (!s)
		return (NULL);
	strsize = ft_strlen(s);
	if (start >= strsize)
		start = strsize;
	if (len > strsize - start)
		len = strsize - start;
	str = (char *)ft_calloc(1, sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (s[start])
		ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
/*
int	main(void)
{
	char	*str;
	size_t	size;
	char	*ret;

    str = "0123456789123456789";
	size = 10;
	ret = ft_substr(str, 7, 3);
	printf("r=%s",ret);
	free(ret);
}
*/
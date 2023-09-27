/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:13:42 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/24 21:33:35 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	if (!s)
		return (0);
	while (s && s[length])
		length++;
	return (length);
}
/*
#include <stdio.h>
#include <string.h>

int	main (void)
{
	char	*s1;
	char	*s2;

	s1 = "re";
	s2 = "Test string";
	printf("string: %s length: %ld\n", s1, ft_strlen(s1));
	printf("string: %s length: %ld\n", s2, ft_strlen(s2));
	printf("string: %s length: %ld\n", s1, strlen(s1));
	printf("string: %s length: %ld\n", s2, strlen(s2));
}
*/

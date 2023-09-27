/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:13:41 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/27 19:54:15 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_of_int(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		n *= (-1);
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

static char	*int_min(void)
{
	char	*nb;

	nb = malloc(sizeof(char) * 12);
	nb[0] = '-';
	nb[1] = '2';
	nb[2] = '1';
	nb[3] = '4';
	nb[4] = '7';
	nb[5] = '4';
	nb[6] = '8';
	nb[7] = '3';
	nb[8] = '6';
	nb[9] = '4';
	nb[10] = '8';
	nb[11] = '\0';
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*nb;
	size_t	size;
	size_t	i;

	if (n == -2147483648)
		return (int_min());
	size = size_of_int(n);
	nb = ft_calloc(sizeof(char), size);
	if (!nb)
		return (NULL);
	i = size - 2;
	if (n == 0)
		nb[i] = '0';
	if (n < 0)
	{
		nb[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		nb[i] = n % 10 + '0';
		i--;
		n /= 10;
	}
	return (nb);
}

// static int	ft_sizeofn(long m)
// {
// 	int	i;

// 	i = 1;
// 	if (m < 0)
// 		i++;
// 	while (m > 9 || m < -9)
// 	{
// 		if (m < 0)
// 			m = -m;
// 		m = m / 10;
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_itoa(int n)
// {
// 	char		*ptr;
// 	int			len;
// 	long long	nlong;

// 	nlong = n;
// 	len = ft_sizeofn(nlong);
// 	ptr = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!ptr)
// 		return (NULL);
// 	ptr[len] = '\0';
// 	if (n == 0)
// 		ptr[0] = '0';
// 	if (nlong < 0)
// 	{
// 		ptr[0] = '-';
// 		nlong = -nlong;
// 	}
// 	while (len-- >= 0 && nlong > 0  && ptr[len] && ptr[len] != '-')
// 	{
// 		ptr[len] = nlong % 10 + '0';
// 		nlong = nlong / 10;
// 	}
// 	return (ptr);
// }
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("%s\n", ft_itoa(-22));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1000034));
	printf("%s\n", ft_itoa(-1));
	printf("%s\n", ft_itoa(3434));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648LL));
	return (1);
}
*/
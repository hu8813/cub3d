/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:04:25 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

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

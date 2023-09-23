/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:08:55 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(unsigned char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		len += write(1, "(null)", 6);
		return (len);
	}
	while (s[len])
	{
		write(1, &s[len], 1);
		len++;
	}
	return (len);
}

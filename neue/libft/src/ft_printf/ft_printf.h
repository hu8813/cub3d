/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:03:25 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		ft_putchar(char c);
void	ft_putnbr(long nb, int *len);
void	ft_putnbr_pos(unsigned int n, int *len);
int		ft_putstr(unsigned char *s);
void	ft_puthexa(unsigned int nb, int *len);
void	ft_puthexa_maj(unsigned int nb, int *len);
void	ft_putptr(unsigned long long ptr, int *len);

#endif

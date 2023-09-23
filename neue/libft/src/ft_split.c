/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:09:07 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	cmpt_words(const char *s, char c)
{
	size_t	i;
	size_t	cmpt;

	i = 0;
	if (s[i] == c || s[i] == 0)
		cmpt = 0;
	else
		cmpt = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			cmpt++;
		i++;
	}
	return (cmpt + 1);
}

static char	**fill_tab(const char *s, char c, char **str)
{
	unsigned int	i;
	size_t			len;
	size_t			cmp;

	i = 0;
	len = 0;
	cmp = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i + len] != c && s[i + len])
			len++;
		if (len > 0)
		{
			str[cmp] = ft_substr(s, i, len);
			cmp++;
		}
		i += len;
		while (s[i] == c && s[i])
			i++;
		len = 0;
	}
	str[cmp] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (cmpt_words(s, c)));
	if (!str)
		return (NULL);
	str = fill_tab(s, c, str);
	return (str);
}

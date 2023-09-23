/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:09:48 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tmp;

	result = NULL;
	if (!lst)
		return (result);
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
			del(tmp->content);
		else
			ft_lstadd_back(&result, tmp);
		lst = lst->next;
	}
	return (result);
}

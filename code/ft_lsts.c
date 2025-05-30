/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:19:23 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:21:19 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_lstadd_back(t_list **lst, t_list *n)
{
	t_list	*swap;

	if (!lst || !n)
		return ;
	if (*lst == NULL)
	{
		*lst = n;
		return ;
	}
	swap = *lst;
	while (swap->next)
		swap = swap->next;
	swap->next = n;
}

void	ft_lstadd_front(t_list **lst, t_list *n)
{
	if (lst && n)
	{
		n->next = *lst;
		*lst = n;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

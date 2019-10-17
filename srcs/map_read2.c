/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:16:10 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:27:47 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

int			clean(t_list **head, t_wolf **wolf)
{
	t_list	*next;

	if (head)
		while (*head)
		{
			next = (*head)->next;
			ft_memdel(&((*head)->content));
			ft_memdel((void**)head);
			*head = next;
		}
	if (wolf)
		if (*wolf)
			if ((*wolf)->block)
				free((*wolf)->block);
	return (1);
}

int			ft_nbofwords(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	if (!s || !c)
		return (0);
	nb = 0;
	i = 0;
	if (s[0] != c)
		nb++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			nb++;
		i++;
	}
	return ((int)nb);
}

void		ft_lstrev(t_list **alst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

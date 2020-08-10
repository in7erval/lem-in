/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:21:52 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:21:54 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	swap(void **a, void **b)
{
	void *buf;

	buf = *a;
	*a = *b;
	*b = buf;
}

static int	sort(void **array, size_t size, int (*cmp)(void *, void *))
{
	int		is_swap;
	size_t	i;

	is_swap = 1;
	i = 0;
	while (i < size - 1)
	{
		if ((*cmp)(array[i], array[i + 1]) > 0)
		{
			is_swap = 0;
			swap(&array[i], &array[i + 1]);
		}
		i++;
	}
	return (is_swap);
}

void		sort_array(void **array, size_t size, int (*cmp)(void *, void *))
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (sort(array, size - i, cmp))
			return ;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_answer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:21:38 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:21:45 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_answer		*ft_init_answer(void)
{
	t_answer	*answer;

	answer = (t_answer *)malloc(sizeof(t_answer));
	answer->round = 0;
	answer->path = 0;
	answer->rounds = NULL;
	return (answer);
}

void			ft_answer_add_round(t_answer *answer)
{
	t_round	*round;
	t_list	*new;

	round = ft_memalloc(sizeof(t_round));
	new = ft_lstnew(round, sizeof(t_round));
	ft_lstadd(&(answer->rounds), new);
	answer->round++;
}

void			ft_answer_add_move(t_answer *answer, t_room *to)
{
	t_round	*round;
	t_list	*new;
	t_move	*move;

	move = ft_memalloc(sizeof(t_move));
	move->ant_number = to->ant_number;
	move->dest = to;
	new = ft_lstnew(move, sizeof(t_move));
	round = (t_round *)answer->rounds->content;
	ft_lstadd(&round->moves, new);
}

static void		free_round(t_round **round)
{
	t_list *kill;
	t_list *buf;

	if (round && *round)
	{
		buf = (*round)->moves;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free(kill->content);
			free(kill);
		}
		free(*round);
		*round = NULL;
	}
}

void			free_answer(t_answer **answer)
{
	t_list *kill;
	t_list *buf;

	if (answer && *answer)
	{
		buf = (*answer)->rounds;
		while (buf)
		{
			kill = buf;
			buf = buf->next;
			free_round((t_round **)&(kill->content));
			free(kill);
		}
		free(*answer);
		*answer = NULL;
	}
}

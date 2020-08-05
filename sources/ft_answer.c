#include "lem_in.h"

t_answer	*ft_init_answer(void)
{
	t_answer *answer;

	answer = (t_answer *) malloc(sizeof(t_answer));
	answer->round = 0;
	answer->path = 0;
	answer->rounds = NULL;
	return (answer);
}

void		ft_answer_add_round(t_answer *answer)
{
	t_round	*round;
	t_list	*new;

	round = ft_memalloc(sizeof(t_round));
	new = ft_lstnew(round, sizeof(t_round));
	ft_lstadd(&(answer->rounds), new);
	answer->round++;
}

void		ft_answer_add_move(t_answer *answer, t_room *to)
{
	t_round	*round;
	t_list	*new;
	t_move	*move;

	move = ft_memalloc(sizeof(t_move));
	move->path_number = answer->path;
	move->ant_number = to->ant_number;
	move->dest = to;
	new = ft_lstnew(move, sizeof(t_move));
	round = (t_round *)answer->rounds->content;
	ft_lstadd(&round->moves, new);
}
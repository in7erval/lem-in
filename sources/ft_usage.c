#include "lem_in.h"

void	ft_bonus(int argc, char **argv, t_lemin *lemin)
{
	if (argc == 2 && !ft_strcmp(argv[1], "-c"))
		lemin->c_bonus = 1;
	else if (argc == 2 && !ft_strcmp(argv[1], "-p"))
		lemin->p_bonus = 1;
	else if ((argc == 2 && (!ft_strcmp(argv[1], "-cp") ||
	!ft_strcmp(argv[1], "-pc"))) || (argc == 3 &&
	((!ft_strcmp(argv[1], "-c") && !ft_strcmp(argv[2], "-p")) ||
	(!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		lemin->c_bonus = 1;
		lemin->p_bonus = 1;
	}
}

int		check_usage(int argc, char **argv)
{
	if (argc > 3 || (argc == 2 && (ft_strcmp(argv[1], "-c") &&
		ft_strcmp(argv[1], "-p") && ft_strcmp(argv[1], "-pc") &&
		ft_strcmp(argv[1], "-cp"))) || (argc == 3 &&
		!((!ft_strcmp(argv[1], "-c") || !ft_strcmp(argv[2], "-p"))
		|| (!ft_strcmp(argv[1], "-p") && !ft_strcmp(argv[2], "-c")))))
	{
		ft_printf("{white}{bold}Usage:{eoc} ./lemin [-{red}c{eoc}{yellow}"
				  "p{eoc}] < file_with_map\n{white}{bold}Options:{eoc}\n\t{red}-c\t"
				  "Print cleaned map{eoc}\n\t{yellow}-p\tPrint paths{eoc}\n");
		return (1);
	}
	return (0);
}


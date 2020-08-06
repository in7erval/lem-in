#include "lem_in.h"

static int 	parse_arg(char *str, t_options *options)
{
	int i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == 'c')
			options->c_bonus = 1;
		else if (str[i] == 'p')
			options->p_bonus = 1;
		else if (str[i] == 'r')
			options->r_bonus = 1;
		else
			return (0);
		i++;
	}
	return (1);

}

static int 	check_correct_params(int argc, char **argv, t_options *options)
{
	int 	i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (!parse_arg(argv[i], options))
			return (0);
		i++;
	}
	return (1);
}


int		check_usage(int argc, char **argv, t_options *options)
{
	if (!check_correct_params(argc, argv, options))
	{
		ft_printf("{white}{bold}Usage:{eoc} ./lemin [-{red}c{yellow}"
					"p{cyan}r{eoc}] < file_with_map\n{white}{bold}Options:"
					"{eoc}\n\t{red}-c\tPrint cleaned map{eoc}"
					"\n\t{yellow}-p\tPrint paths{eoc}"
					"\n\t{cyan}-r\tPrint rooms{eoc}\n");
		return (1);
	}
	return (0);
}


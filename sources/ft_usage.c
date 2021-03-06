/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:25:01 by htrent            #+#    #+#             */
/*   Updated: 2020/08/10 15:25:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	all_options(t_options *options)
{
	options->c_bonus = 1;
	options->p_bonus = 1;
	options->r_bonus = 1;
	options->n_bonus = 1;
}

static int	parse_arg(char *str, t_options *options)
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
		else if (str[i] == 'n')
			options->n_bonus = 1;
		else if (str[i] == 'd')
			all_options(options);
		else
			return (0);
		i++;
	}
	return (1);
}

static int	check_correct_params(int argc, char **argv, t_options *options)
{
	int	i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (!parse_arg(argv[i], options))
			return (0);
		i++;
	}
	return (1);
}

static void	init_options(t_options *options)
{
	options->r_bonus = 0;
	options->p_bonus = 0;
	options->c_bonus = 0;
	options->n_bonus = 0;
}

int			check_usage(int argc, char **argv, t_options *options)
{
	init_options(options);
	if (!check_correct_params(argc, argv, options))
	{
		ft_printf("\n{white}{bold}Usage:{eoc} ./lemin [-{red}c{yellow}"
					"p{cyan}r{magenta}d{green}n{eoc}] < file_with_map\n"
					"{white}{bold}Options:"
					"{eoc}\n\t{red}-c\tPrint cleaned map{eoc}"
					"\n\t{yellow}-p\tPrint paths{eoc}"
					"\n\t{cyan}-r\tPrint rooms{eoc}"
					"\n\t{green}-n\tNot strict parsing{eoc}"
					"\n\t{magenta}-d\tDebug mode{eoc}\n\n");
		return (1);
	}
	return (0);
}

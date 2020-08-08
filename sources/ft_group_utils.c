#include "lem_in.h"

void	print_group(t_group *group, int flag)
{
	int	i;

	if (!flag)
		return ;
	i = 0;
	ft_printf("\n------------{underline}PATHES{eoc}------------\n");
	ft_printf("{green}Path_count: {bold}%d\t{eoc}{green}Total_rounds:"
				" {bold}%d{eoc}\n", group->path_count, group->total_rounds);
	while (i < group->path_count)
	{
		ft_printf("{white}{bold}Path{red}{bold}#%d{eoc}({cyan}{bold}"
				"len=%d{eoc}): ", (i + 1), group->paths[i]->len);
		print_path(group->paths[i]);
		i++;
	}
	ft_printf("---------------------------------\n");
}

void	free_group(t_group *group)
{
	int i;

	i = 0;
	while (i < group->path_count)
		free_path(group->paths[i++]);
	free(group->paths);
	free(group->ants);
	free(group);
}

#include "cub3d.h"

void	ft_error(t_info *info, char *str)
{
	int	i;

	i = 0;
	printf("Error\n");
	printf("%s", str);
	if (info->N)
		free(info->N);
	if (info->S)
		free(info->S);
	if (info->W)
		free(info->W);
	if (info->E)
		free(info->E);
	if (info->I)
		free(info->I);
	while (info->map && i < info->row)
	{
		free(info->map[i]);
		i++;
	}
	if (info->map)
		free(info->map);
	ft_error2(info);
}

void	ft_error2(t_info *info)
{


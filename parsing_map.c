#include "cub3d.h"

int	make_map(t_info *info, char *str, int j)
{
	static int	i = 0;

	if (!(info->map[i] = (char *)malloc(sizeof(char) * (info->col + 1))))
		return (info->error = 2);// in gnl there is error ==1// add when error == 2
	while (str[j] != '\0')
	{
		if (str[j] == 'N' || str[j] == 'S' || str[j] == 'W' || str[j] == 'E')
		{
			info->map[i][j] = '0';
			info->posNEWS = str[j];
			info->posX = i;
			info->posY = j;
		}
		else if (str[j] == ' ')
			info->map[i][j] = '4';
		else
			info->map[i][j] = str[j];
		j++;
	}
	while (j < info->col)
		info->map[i][j++] = '4';
	info->map[i][j] = '\0';
	i++;
	return (0);
}

int	check_valid_map(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i] != '\0')
	{
		while (info->map[i][j] != '\0')
		{
			if (info->map[i][j] == '0' || info->map[i][j] == '2')
			{
				if (check_udrl(info, i, j) != 0)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

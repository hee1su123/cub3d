#include "cub3d.h"

int	check_udrl(t_info *info, int i, int j)
{
	if (i == 1 || i == info->row - 1 || j = 1)
		return (-1);
	if (info->map[i + 1][j] == '4' || info->map[i + 1][i] == '\0')
		return (-1);
	if (info->map[i][j + 1] == '4' || info->map[i][j + 1] == '\0')
		return (-1);
	if (info->map[i - 1][j] == '4' || info->map[i - 1][j] == '\0')
		return (-1);
	if (info->map[i][j - 1] == '4' || info->map[i][j - 1] == '\0')
		return (-1);
	return (0);// if map[1][j] it can't be 0 or 2
	// and aloso if map[last][j] it can't be 0 or 2
	// and if map[i][1] it can't be 0 or 2
	// and map[i][last] is different becase there is '\0'
}


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
			info->startNEWS = str[j];
			info->startX = i;
			info->startY = j;
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

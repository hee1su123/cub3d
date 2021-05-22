#include "cub3d.h"

int	check_map_size(t_info *info, char *str)
{
	int	i;

	i = 0;
	if (info->N == 0 || info->S == 0 || info->W == 0 || info->E == 0 || info->I == 0  || info->F == -1 || info->C == -1)
		return (info->error = 1);
	if (ft_strlen(str) > info->col)
		info->col = ft_strlen(str);
	info->row++;
}


int	resolution_color(t_info *info, char **str)
{
	int	i;

	i = 0;
	if (*str[i] == 'R')
	{
		if (RenderX != 0 || RenderY != 0)
			return (info->error = 1);
		if (get_render_size(info, *str) != 0)
			return (info->error = 1);
		if (info->RenderX == 0 || info->RenderY == 0)
			return (info->error = 1);
	}
	else if (*str[i] == 'F')
		info->F = get_color(info, *str);		
	else if (*str[i] == 'C')
		info->C = get_color(info, *str);
	return (0);
}

int	path_texture(t_info *info, char **texture, char *str)
{
	int	i;
	int	j;

	if (*texture != 0)
		return (info->error = 1);
	if (ft_strchr(str, '.') == 0 || ft_strchr(str, '/') == 0)
		return (info->error = 1);
	i = (str[i] == 'S' && str[i + 1] != 'O') ? 1 : 2;
	while (str[i] != '.')
	{
		if(str[i++] != ' ')
			return (info->error = 1);
	}
	if (!(*texture = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1))))
		return (info->error = 1);
	j = 0;
	while (str[i] != '\0')
		(*texture)[j++] = str[i++];// this works i tested
	if (j <= 3)
		return (info->error = 1);
	(*texture)[j] = '\0';
	return (0);
}


int	parsing_line(t_info *info, char **str)
{
	int	i;

	i = 0;
	if (str[i] == '\n' && info->inmap == 0)
		return (0);
	else if (str[i] == 'N' && str[i + 1] == 'O' && info->inmap == 0)
		path_texture(info, &info->N, *str);
	else if (str[i] == 'S' && str[i + 1] == 'O' && info->inmap == 0)
		path_texture(info, &info->S, *str);
	else if (str[i] == 'W' && str[i + 1] == 'E' && info->inmap == 0)
		path_texture(info, &info->W, *str);
	else if (str[i] == 'E' && str[i + 1] == 'A' && info->inmap == 0)
		path_texture(info, &info->E, *str);
	else if (str[i] == 'S' && str[i + 1] != 'O' && info->inmap == 0)
		path_texture(info, &info->I, *str);
	else if (str[i] == 'R' || str[i] == 'F' || str[i] == 'C' && info->inmap == 0)
		resolution_color(info, str);
	else if (info->inmap == 1 || check_inmap(info, *str) != 0)
		check_map_size(info, *str);// change info->inmap value // check also \n between the map
	else
		info->error = 1;
	return (0);
}

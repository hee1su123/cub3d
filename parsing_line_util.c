#include "cub3d.h"

int	get_render_size(t_info *info, char *str)
{
	int	i;
	int	x;
	int	y;

	i = 1;
	x = 0;
	y = 0;
	while (str[i] == ' ')
		i++;
	while (ft_strchr("0123456789", str[i]) != 0)
		x = (x * 10) + (str[i++] - 48);
	while (str[i] == ' ')
		i++;
	while (str[i] && ft_strchr("0123456789", str[i]) != 0)
		y = (y * 10) + (str[i++] - 48);
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (-1);
	if (x > 21474836 || y > 21474836)
		return (-1);
	info->RenderX = x;
	info->RenderY = y;
	return (0);
}

int	check_color_str(t_info *info, char *str, int **color, int i)
{
	int	num;
	int	flag;

	flag = 0;
	num = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("0123456789", str[i]) != NULL)
			num = num * 10 + (str[i] - 48);
		else if (str[i] == ',' && flag < 2)
		{
			*color[flag++] = num;
			num = 0;
		}
		else if (str[i] == '\0' && flag == 2)
			*color[flag] = num;
		else
			return (-1);
		i++;
	}
	return (0);
}

int	get_color(t_info *info, char *str)
{
	int	i;
	int	ret;
	int	color[3];

	i = 1;
	while (str[i] == ' ')
		i++;
	if (check_color_str(info, str, &color, i) != 0)
	{
		info->error = 1;
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			return (-1);
		i++;
	}
	ret = (color[0]<<16 | color[1]<<8 | color[2]);
	return (ret);
}

int	check_inmap(t_info *info, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (ft_strchr("012NSWE \n", str[i]) == NULL)
		{
			info->error = 1;
			return (0);
		}
		

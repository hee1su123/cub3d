#include "cub3d.h"

void	ft_init_info(t_info *info)
{
	info.save = 0;
	info.error = 0;
	info.inmap = 0;
	info.F = -1;
	info.C = -1;
	info.RenderX = 0;
	info.RenderY = 0;
	info.I = NULL;
	info.N = NULL;
	info.S = NULL;
	info.W = NULL;
	info.E = NULL;
	info.row = 0;
	info.col = 0;
	info.map = NULL;
	info.startNEWS = '\0';
	startX = 0;
	startY = 0;
	num_spr = 0;
}

void	ft_init_dir(t_info *info)
{
	if (info->startNEWS == 'N')
	{
		info->ray.dirY = -1;
		info->ray.planeX = 0.66;
	}
	else if (info->startNEWS == 'S')
	{
		info->ray.dirY = 1;
		info->ray.planeX = -0.66;
	}
	else if (info->startNEWS == 'W')
	{
		info->ray.dirX = -1;
		info->ray.planeY = -0.66;
	}
	else (info->startNEWS == 'E')
	{
		info->ray.dirX = 1;
		info->ray.planeY = 0.66;
	}
}

}

void	ft_init_ray(t_info *info)
{
}

void	ft_init_ray2(t_info *info)
{
}



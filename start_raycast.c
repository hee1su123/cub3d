#include "cub3d.h"

int	raycast(t_info *info)
{
	info->ray.x = 0;

	while (info->ray.x < info->RenderX)
	{
		ft_init_ray2(info);
		//several fuctions
	}
	mlx_put_image_to_window(info->ray.mlx, info->ray.win, info->ray.img.img, 0, 0);
	mv_front_back(info);
	mv_right_left(info);
	rt_right_left(info);
	return (0);
}

void	ft_mlx2(t_info *info)
{
	get_texture(info);
	info->ray.win = mlx_new_window(info->ray.mlx, info->RenderX, info->RenderY, "mlx");
	info->ray.img.img = mlx_new_image(info->ray.mlx, info->RenderX, info->RenderY);
	info->ray.img.data = (int *)mlx_get_data_addr(info->ray.img.img, &info->ray.img.bpp, &info->ray.img.size_l, &info->ray.img.endian);
	mlx_loop_hook(info->ray.mlx, &raycast, info);
	mlx_hook(info->ray.win, X_EVENT_KEY_PRESS, 0, &key_press, info);
	mlx_hook(info->ray.win, X_EVENT_KEY_RELEASE, 0, &key_release, info);
	mlx_loop(info);
}

void	ft_mlx(t_info *info)
{
	int	i;

	ft_init_ray(info);//init structure raycast
	if (!(info->ray.mlx = mlx_init()))
		ft_error(info, "failed mlx_init");
	mlx_get_screen_size(info->ray.mlx, info->screenX, info->screenY);
	info->RenderX = (info->RenderX > info->screenX) ? info->screenX : info->RenderX;
	info->RenderY = (info->RenderY > info->screenY) ? info->screenY : info->RenderY;
	if (!(info->ray.buf = (int **)malloc(sizeof(int *) * (RenderY + 1))))
		ft_error(info, "failed buf malloc");
	if (!(info->ray.*buf = (int *)malloc(sizeof(int) * (RenderX + 1))))
		ft_error(info, "failed *buf malloc");
	if (!(info->ray.texture = (int **)malloc(sizeof(int *) * 5)))
		ft_error(info, "failed texture malloc");
	i = 0;
	while (i < 5)
	{
		if (!(info->ray.texture[i] = (int *)malloc(sizeof(int) * (texH * texW))))
			ft_error(info, "failed *texture malloc");
		i++;
	}
	ft_init_buf_tex(info);//I need a function to initialize **buf and **texture into 0
	ft_mlx2(info);
}

void	start_raycast(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_errors(info);//verify errors occured before
	while (i < info->row)
	{
		while (j < info->col)
		{
			if (info->map[i][j++] == '2')
				info->num_spr++;
		}
		i++
	}
	// sprite related memory allocation
	ft_mlx(info);
}

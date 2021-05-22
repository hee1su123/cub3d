#include "cub3d.h"

void	ft_init_texture(t_recup *recup)
{
	if (recup->ray.side == 0 && recup->ray.raydirx < 0)
		recup->t.texdir = 0;
	if (recup->ray.side == 0 && recup->ray.raydirx >= 0)
		recup->t.texdir = 1;
	if (recup->ray.side == 1 && recup->ray.raydiry < 0)
		recup->t.texdir = 2;
	if (recup->ray.side == 1 && recup->ray.raydiry >= 0)
		recup->t.texdir = 3;
	if (recup->ray.side == 0)
		recup->t.wallx = recup->ray.posy + recup->ray.perpwalldist \
						* recup->ray.raydiry;
	else
		recup->t.wallx = recup->ray.posx + recup->ray.perpwalldist \
						* recup->ray.raydirx;
	recup->t.wallx -= floor((recup->t.wallx));
}

void	ft_draw_texture(t_recup *recup, int x, int y)
{
	y = recup->ray.drawstart - 1;
	ft_init_texture(recup);
	recup->t.step = 1.0 * recup->texture[0].height / recup->ray.lineheight;
	recup->t.texx = (int)(recup->t.wallx * (double)recup->texture
			[recup->t.texdir].width);
	if (recup->ray.side == 0 && recup->ray.raydirx > 0)
		recup->t.texx = recup->texture[recup->t.texdir].width -
			recup->t.texx - 1;
	if (recup->ray.side == 1 && recup->ray.raydiry < 0)
		recup->t.texx = recup->texture[recup->t.texdir].width -
			recup->t.texx - 1;
	recup->t.texpos = (recup->ray.drawstart - recup->ry / 2 +
			recup->ray.lineheight / 2) * recup->t.step;
	while (++y <= recup->ray.drawend)
	{
		recup->t.texy = (int)recup->t.texpos &
			(recup->texture[recup->t.texdir].height - 1);
		recup->t.texpos += recup->t.step;
		if (y < recup->ry && x < recup->rx)
			recup->data.addr[y * recup->data.line_length / 4 + x] =
				recup->texture[recup->t.texdir].addr[recup->t.texy *
					recup->texture[recup->t.texdir].line_length /
					4 + recup->t.texx];
	}
}

int		ft_color_column(t_recup *recup)
{
	int j;
	int i;

	j = -1;
	recup->ray.drawend = recup->ry - recup->ray.drawstart;
	i = recup->ray.drawend;
	while (++j < recup->ray.drawstart)
		recup->data.addr[j * recup->data.line_length / 4 +
			recup->ray.x] = recup->c;
	if (j <= recup->ray.drawend)
		ft_draw_texture(recup, recup->ray.x, j);
	j = i;
	while (++j < recup->ry)
		recup->data.addr[j * recup->data.line_length / 4 +
			recup->ray.x] = recup->f;
	return (0);
}

void	ft_drawstartend(t_recup *recup)
{
	if (recup->ray.side == 0)
		recup->ray.perpwalldist = ((double)recup->ray.mapx - \
				recup->ray.posx + (1 - (double)recup->ray.
				stepx) / 2) / recup->ray.raydirx;
	else
		recup->ray.perpwalldist = ((double)recup->ray.mapy - \
				recup->ray.posy + (1 - (double)recup->ray.
				stepy) / 2) / recup->ray.raydiry;
	recup->ray.lineheight = (int)(recup->ry / recup->ray.perpwalldist);
	recup->ray.drawstart = -recup->ray.lineheight / 2 + recup->ry / 2;
	if (recup->ray.drawstart < 0)
		recup->ray.drawstart = 0;
	recup->ray.drawend = recup->ray.lineheight / 2 + recup->ry / 2;
	if (recup->ray.drawend >= recup->ry || recup->ray.drawend < 0)
		recup->ray.drawend = recup->ry - 1;
}

void	ft_incrementray(t_recup *recup)
{
	while (recup->ray.hit == 0)
	{
		if (recup->ray.sidedistx < recup->ray.sidedisty)
		{
			recup->ray.sidedistx += recup->ray.deltadistx;
			recup->ray.mapx += recup->ray.stepx;
			recup->ray.side = 0;
		}
		else
		{
			recup->ray.sidedisty += recup->ray.deltadisty;
			recup->ray.mapy += recup->ray.stepy;
			recup->ray.side = 1;
		}
		if (recup->map[recup->ray.mapx][recup->ray.mapy] == '1')
			recup->ray.hit = 1;
	}
	ft_drawstartend(recup);
}

void	ft_stepsidedist(t_recup *recup)
{
	if (recup->ray.raydirx < 0)
	{
		recup->ray.stepx = -1;
		recup->ray.sidedistx = (recup->ray.posx - recup->ray.mapx) \
							* recup->ray.deltadistx;
	}
	else
	{
		recup->ray.stepx = 1;
		recup->ray.sidedistx = (recup->ray.mapx + 1.0 - recup->ray.posx) \
							* recup->ray.deltadistx;
	}
	if (recup->ray.raydiry < 0)
	{
		recup->ray.stepy = -1;
		recup->ray.sidedisty = (recup->ray.posy - recup->ray.mapy) \
							* recup->ray.deltadisty;
	}
	else
	{
		recup->ray.stepy = 1;
		recup->ray.sidedisty = (recup->ray.mapy + 1.0 - recup->ray.posy) \
							* recup->ray.deltadisty;
	}
	ft_incrementray(recup);
}


void	ft_init_more3(t_recup *recup)
{
	if (recup->ray.raydiry == 0)
		recup->ray.deltadistx = 0;
	else if (recup->ray.raydirx == 0)
		recup->ray.deltadistx = 1;
	else
		recup->ray.deltadistx = sqrt(1 + (recup->ray.raydiry
			* recup->ray.raydiry) / (recup->ray.raydirx *
			recup->ray.raydirx));
	if (recup->ray.raydirx == 0)
		recup->ray.deltadisty = 0;
	else if (recup->ray.raydiry == 0)
		recup->ray.deltadisty = 1;
	else
		recup->ray.deltadisty = sqrt(1 + (recup->ray.raydirx *
			recup->ray.raydirx) / (recup->ray.raydiry *
			recup->ray.raydiry));
}

void	ft_initialisation3(t_recup *recup)
{
	recup->ray.hit = 0;
	recup->ray.perpwalldist = 0;
	recup->ray.camerax = 2 * recup->ray.x / (double)recup->rx - 1;
	recup->ray.raydirx = recup->ray.dirx + recup->ray.planx * \
						recup->ray.camerax;
	recup->ray.raydiry = recup->ray.diry + recup->ray.plany * \
						recup->ray.camerax;
	recup->ray.mapx = (int)recup->ray.posx;
	recup->ray.mapy = (int)recup->ray.posy;
	recup->ray.movespeed = 0.1;
	recup->ray.rotspeed = 0.033 * 1.8;
	ft_init_more3(recup);
}

int		ft_raycasting(t_recup *recup)
{
	recup->ray.x = 0;
	while (recup->ray.x < recup->rx)
	{
		ft_initialisation3(recup);
		ft_stepsidedist(recup);
		ft_color_column(recup);
		recup->s.zbuffer[recup->ray.x] = recup->ray.perpwalldist;
		recup->ray.x++;
	}
	ft_sprite(recup);
	if (recup->save == 1)
		ft_save(recup);
	mlx_put_image_to_window(recup->data.mlx_ptr, recup->data.mlx_win,
			recup->data.img, 0, 0);
	ft_forward_back(recup);
	ft_left_right(recup);
	ft_rotate_right_left(recup);
	ft_swap(recup);
	return (0);
}

void	ft_get_texture_adress(t_recup *recup)
{
	recup->texture[0].addr = (int *)mlx_get_data_addr(recup->texture[0].img,
			&recup->texture[0].bits_per_pixel,
			&recup->texture[0].line_length, &recup->texture[0].endian);
	recup->texture[1].addr = (int *)mlx_get_data_addr(recup->texture[1].img,
			&recup->texture[1].bits_per_pixel,
			&recup->texture[1].line_length, &recup->texture[1].endian);
	recup->texture[2].addr = (int *)mlx_get_data_addr(recup->texture[2].img,
			&recup->texture[2].bits_per_pixel,
			&recup->texture[2].line_length, &recup->texture[2].endian);
	recup->texture[3].addr = (int *)mlx_get_data_addr(recup->texture[3].img,
			&recup->texture[3].bits_per_pixel,
			&recup->texture[3].line_length, &recup->texture[3].endian);
	recup->texture[4].addr = (int *)mlx_get_data_addr(recup->texture[4].img,
			&recup->texture[4].bits_per_pixel,
			&recup->texture[4].line_length, &recup->texture[4].endian);
}

void	ft_get_texture(t_recup *recup)
{
	if (!(recup->texture[0].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
					recup->no, &(recup->texture[0].width),
					&(recup->texture[0].height))))
		ft_error(recup, "Texture SO\n");
	if (!(recup->texture[1].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
					recup->so, &(recup->texture[1].width),
					&(recup->texture[1].height))))
		ft_error(recup, "Texture NO\n");
	if (!(recup->texture[2].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
					recup->we, &(recup->texture[2].width),
					&(recup->texture[2].height))))
		ft_error(recup, "Texture EA\n");
	if (!(recup->texture[3].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
					recup->ea, &(recup->texture[3].width),
					&(recup->texture[3].height))))
		ft_error(recup, "Texture WE\n");
	if (!(recup->texture[4].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
					recup->sp, &(recup->texture[4].width),
					&(recup->texture[4].height))))
		ft_error(recup, "Texture S\n");
	ft_get_texture_adress(recup);
}

void	ft_init_dir(t_recup *recup)
{
	if (recup->depart == 'N')
		recup->ray.dirx = -1;
	if (recup->depart == 'S')
		recup->ray.dirx = 1;
	if (recup->depart == 'E')
		recup->ray.diry = 1;
	if (recup->depart == 'W')
		recup->ray.diry = -1;
	if (recup->depart == 'N')
		recup->ray.plany = 0.66;
	if (recup->depart == 'S')
		recup->ray.plany = -0.66;
	if (recup->depart == 'E')
		recup->ray.planx = 0.66;
	if (recup->depart == 'W')
		recup->ray.planx = -0.66;
}

void	ft_initialisation2(t_recup *recup)
{
	if (!(recup->s.zbuffer = (double *)malloc(sizeof(double) * recup->rx)))
		exit(0);
	recup->data.forward = 0;
	recup->data.back = 0;
	recup->data.left = 0;
	recup->data.right = 0;
	recup->data.rotate_right = 0;
	recup->data.rotate_left = 0;
	recup->ray.posx = (double)recup->dx + 0.5;
	recup->ray.posy = (double)recup->dy + 0.5;
	recup->ray.dirx = 0;
	recup->ray.diry = 0;
	recup->ray.planx = 0;
	recup->ray.plany = 0;
	ft_init_dir(recup);
}

int		ft_mlx(t_recup *recup)
{
	ft_initialisation2(recup);
	if (!(recup->data.mlx_ptr = mlx_init()))
		ft_error(recup, "Mlx init impossible\n");
	mlx_get_screen_size(recup->data.mlx_ptr, &recup->screenx, &recup->screeny);
	recup->rx = (recup->rx > recup->screenx) ? recup->screenx : recup->rx;
	recup->ry = (recup->ry > recup->screeny) ? recup->screeny : recup->ry;
	ft_get_texture(recup);
	recup->data.img = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr = (int *)mlx_get_data_addr(recup->data.img, &recup->data.
			bits_per_pixel, &recup->data.line_length, &recup->data.endian);
	if (recup->save == 1)
		ft_raycasting(recup);
	recup->data.mlx_win = mlx_new_window(recup->data.mlx_ptr, recup->rx,
			recup->ry, "Hello world!");
	recup->data.img2 = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr2 = (int *)mlx_get_data_addr(recup->data.img2, &recup->
			data.bits_per_pixel, &recup->data.line_length, &recup->data.endian);
	mlx_loop_hook(recup->data.mlx_ptr, ft_raycasting, recup);
	mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
	mlx_hook(recup->data.mlx_win, 2, 1L << 0, ft_key_press, recup);
	mlx_hook(recup->data.mlx_win, 3, 1L << 1, ft_key_release, recup);
	mlx_loop(recup->data.mlx_ptr);
	return (0);
}

void	ft_init_sprite2(t_recup *recup, int i, int j, int v)
{
	i = i - 1;
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
		{
			if (recup->map[i][j] == '2')
			{
				recup->sxy[v].x = (double)i + 0.5;
				recup->sxy[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}

void	ft_init_sprite(t_recup *recup)
{
	int i;
	int j;

	i = -1;
	recup->s.nbspr = 0;
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
		{
			if (recup->map[i][j] == '2')
				recup->s.nbspr += 1;
		}
	}
	if (!(recup->sxy = (t_sprxy *)malloc(sizeof(t_sprxy) * recup->s.nbspr)))
		ft_error(recup, "Malloc sxy*");
	if (!(recup->s.order = (int *)malloc(sizeof(int) * recup->s.nbspr)))
		ft_error(recup, "Malloc s.order*");
	if (!(recup->s.dist = (double *)malloc(sizeof(double) * recup->s.nbspr)))
		ft_error(recup, "Malloc s.dist*");
	ft_init_sprite2(recup, 0, 0, 0);
	ft_mlx(recup);
}
#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <unisdt.h>
# include <stdlib.h>
# include <stdio.h>

# define FORWARD_W	119
# define BACK_S		115
# define RIGHT_D	100
# define LEFT_A		97
# define ROTATE_R
# define ROTATE_L
# define BUFFER_SIZE	4096

typedef struct	s_info
{
	int	error;
	int	save;


}
/* save.c */
int	check_save(t_info *info, char **arg);

/* main.c */
int	check_map(t_info *info, char *arg);
int	parsing_elements(t_info *info, char *arg);
int	parsing_map(t_info *info, char *arg);

/*get_next_line*/
int	get_next_line(int fd, char **line, int error);

#endif
/*
 * info->error
 * 0 : default
 * 1 : error and need to free gnl buff which is static variable
 *
 * the ft_error will end with exti(0) eventually
 */


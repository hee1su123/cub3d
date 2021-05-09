#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <unisdt.h>
# include <stdlib.h>

# define BUFFER_SIZE	4096

typedef struct	s_info
{
	int	error;

}

/* main.c */
int	check_map(t_info *info, char *argv);
int	ft_parsing(t_info, char *argv);

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


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
int	get_next_line(t_info *info, int fd, char **str);
#endif
/* error
 * 1 : argv[1] is not a .cub file
 * 2 : argv[1] is a directory
 * 3 : 
 * 4
 * 5
 * 6
 * 7
 *
 *
 * the ft_error will end with exti(0) eventually
 */


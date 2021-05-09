#include "cub3d.h"

int	get_next_line(t_info *info, int fd, char **str)
{
	static char	*buff;

	if(fd < 0 || !str)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (read(fd, buff, BUFFER_SIZE) > 0)
	{
		if (check_n(&buff) != 0)
			

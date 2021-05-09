#include "cub3d.h"

int	get_next_line(int fd, char **line, int error)
{
	static char	*save;
	char		*buff;
	int		read_len;
	int		loc_nextline;

	if (error == 1 && backup != NULL)
	{
		free(backup);
		return (-1);
	}
	if (fd < 0 || line == 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((read_len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_len] = '\0';
		temp = backup;
		backup = ft_strjoin(temp, buff);
		if ((loc_newline = check_newline(temp)) >= 0)


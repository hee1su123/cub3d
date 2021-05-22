#include "cub3d.h"

int	split_save(char **save_ad, char **line, int nl)
{
	char	*temp;

	(*save_ad)[nl] = '\0';
	if (!(*line = ft_strdup(*save_ad)))
		return (-1);
	if (!(ft_strlen(*save_ad + nl + 1)))
	{
		free(*save_ad);
		*save_ad = 0;
		return (1);
	}
	if (!(temp = ft_strdup(*save_ad + nl + 1)))
		return (-1);
	free(*save_ad);
	*save_ad = temp;
	return (1);
}

int	check_nextline(char *save)
{
	int	i;

	i = 0;
	while (save[i] != 0 && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		return (i);
	else
		return (-1);
}

int	get_next_line(t_info *info, int fd, char **line)
{
	static char	*save;
	char		*buff;
	int		read_len;
	int		loc_nextline;

	if (info->error == 2 && *save != NULL)
	{
		free(*save);
		ft_error(info, "Error while parsing map");
	}
	if (info->error == 1 && *save != NULL)
	{
		free(*save);
		ft_error(info, "Error while parsing map elements");
	}
	if (fd < 0 || line == 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((read_len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_len] = '\0';
		if (!(save = ft_strjoin(save, buff)))
			return (-1);
		if ((loc_nextline = check_nextline(save)) >= 0)
			return(split_save(&save, line, loc_nextline));
	}
	if (read_len < 0)
		return (-1);
	return (return_gnl(&save, line));
}

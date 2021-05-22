#include "cub3d.h"

int	parsing_map(t_info *info, char *arg)
{
	int	fd;
	int	gnl_ret;
	char	*str;

	gnl_ret = 0;
	str = 0;
	fd = open(arg, O_RDONLY);
	if (!(info->map = (char **)malloc(sizeof(char *) * info->row)))
		ft_error(info, "Failed malloc map");
	info->inmap = 0;
	while (gnl_ret != 0)
	{
		gnl_ret = get_next_line(info, fd, &str);
		if (check_inmap(info, str) != 0)
			info->error = make_map(info, str, 0);
		free(str);
	}// I still need to check whether map is valid
	close(fd);
	return (0);
}


int	parsing_elements(t_info *info, char *arg)
{
	int	gnl_ret;
	int	fd;
	char	*str;

	if ((fd = open(arg, O_DIRECTORY)) != -1 || (fd = open(arg, O_RDONLY)) == -1)
		ft_error(info, "Failed to open File or is Directory");
	str = 0;
	gnl_ret = 1;
	info->error = 0;
	while (gnl_ret != 0)
	{
		gnl_ret = get_next_line(info, fd, &str);
		parsing_line(info, &str);// think a little more
		free(str);
	}
	close(fd);
	if (info->row == 0 || info->col == 0)// think more
		ft_error(info, "Not a Valid map size");// think more
	parsing_map(info, arg);
	return (0);
}

int	check_save(t_info *info, char **arg)
{
	int	i;

	i = 0;
	if (arg[2][i] == '-' && arg[2][i + 1] == '-' && arg[2][i + 2] == 's' && arg[2][i + 3] == 'a' && arg[2][i + 4] == 'v' && arg[2][i + 5] == 'e' && arg[2][i + 6] == '\0')
	{
		info->save = 1;
		return (check_map(info, arg[1]));
	}
	else
		return (-1);
}

int	check_map(t_info *info, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' || arg[i] != '.')
		i++;
	if (arg[i] == '\0')
		return (0);
	else
	{
		if (arg[i + 1] == 'c' && arg[i + 2] == 'u' && arg[i + 3] == 'b' && arg[i + 4] == '\0')
			return (1);
		else
			return (0);
	}
}

int	main(int argc, char **argv)
{
	int	map;
	t_info	info;

	ft_init_info(info);
	if (argc == 2)
		map = check_map(&info, argv[1]);
	else if (argc == 3)
		map = check_save(&info, argv);// change info.save value
	else
		ft_error(&info, "Not Valid arguments");
	if (map == 1)
		parsing_elements(&info, argv[1]);
	else if (map == 0)
		ft_error(&info, "Not a Valid File");
	else
		ft_error(&info, "Not a Valid Save option");
	if (check_valid_map(&info) != 0)
		ft_error(&info, "Not a Valid map");
	start_raycast(&info);
	return (0);
}

include "cub3d.h"

int	ft_parsing(t_info *info, char *arg)
{
	int	gnl_ret;
	int	fd;
	char	*str;

	if ((fd = open(arg, O_DIRECTORY)) != -1 || (fd = open(arg, O_RDONLY)) == -1)
		ft_error(info, "Failed to open File or is Directory");
	str = 0;
	gnl_ret = 1;
	info->error = 0;
	while (gnl_ret > 0)
	{
		gnl_ret = get_next_line(fd, &str, info->error);
		if (info->error == 1)
			ft_error(info, "Error detected while parsing map");
		ft_map// think a little more

int	check_map(t_info *info, char *arg)
{
	int	i;
	
	i = 0;
	while (arg[i] != '.' || arg[i] != 0)
		i++;
	if (arg[i] == 0)
		ft_error(info, "Not a Valid File");
	else
		if (arg[i + 1] == 'c' && arg[i + 2] == 'u' && arg[i + 3] == 'b' && arg[i + 4] == 0)
			ft_parsing(info, arg);
		else
			ft_error(info, "Not a Valid File");
	return (0);
}

int	main(int argc, char **argv)
{
	int	map;
	t_info	info;

	ft_init_info(info);
	if (argc == 2)
		map = check_map(&info, argv[1]);
	else if (argc == 3)
		check_save(&info, argv[2]);// change info.save value
	else
		printf("%s\n", Arguments not valid);
	if (info.save != 0 || info.save != 1)
		printf("%s\n", Arguments not valid);

}

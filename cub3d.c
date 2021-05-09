include "cub3d.h"

int	ft_parsing(t_info *info, char *argv)
{
	int	gnl_ret;
	int	fd;
	char	*str;

	if ((fd = open(argv, O_DIRECTORY)) != -1 || (fd = open(argv, O_RDONLY)) == -1)
		ft_error(info, "Failed to open File or is Directory");
	str = 0;
	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		gnl_ret = get_next_line(fd, &str, info->error);
		parsing_map(info, &str);


int	check_map(t_info *info, char *argv)
{
	int i;
	
	i = 0;
	while (argv[i] != '.' || argv[i] != 0)
		i++;
	if (argv[i] == 0)
		ft_error(info, "Not a Valid File");
	else
		if (argv[i + 1] == 'c' && argv[i + 2] == 'u' && argv[i + 3] == 'b' && argv[i + 4] == 0)
			ft_parsing(info, argv);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info info;
	ft_init(info);
	//check argc wheter it is 2 or 3
	check_map(&info, argv[1]);
}

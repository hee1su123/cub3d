#include "cub3d.h"

int	check_map(t_info *info, char *argv)
{
	int i;
	
	i = 0;
	while (argv[i] != '.' || argv[i] != 0)
		i++;
	if (argv[i] == 0)
		info->error = 1;
	else
		if (argv[i + 1] == 'c' && argv[i + 2] == 'u' && argv[i + 3] == 'b' && argv[i + 4] == 0)
			ft_parsing(info, argv);
	return (0);

int	main(int argc, char **argv)
{
	t_info info;
	ft_init(info);
	//check argc wheter it is 2 or 3
	check_map(&info, argv[1]);
	check_error(info.error);// check wat numbe error has and do as followed
}

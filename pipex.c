#include "pipex.h"

void	ft_free(t_pipe *data)
{
	int	i;

	i = -1;
	while (data->environ[++i])
		free(data->environ[i]);
	free(data->environ);
	free(data->argv_0);
	free(data->argv_1);
	free(data);
}

void	ft_init(t_pipe **data, char **envp, int envcnt)
{
	int	i;

	i = -1;
	(*data) = (t_pipe *)malloc(sizeof(t_pipe));
	(*data)->environ = (char **)malloc(sizeof(char *) * (envcnt + 1));
	(*data)->argc_0 = 0;
	(*data)->argc_1 = 0;
	(*data)->argv_0 = NULL;
	(*data)->argv_1 = NULL;
	(*data)->fdin = 0;
	(*data)->fdout = 0;
	while (++i < envcnt)
		(*data)->environ[i] = ft_strdup(envp[i]);
}

void	ft_exit(t_pipe *data, int err)
{
	if (err == 1)
		ft_putendl_fd("4 arguments are required", 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	ft_free(data);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*data;
	int		envcnt;

	envcnt = 0;
	while (envp[envcnt])
		envcnt++;
	ft_init(&data, envp, envcnt);
	if (argc != 5)
		ft_exit(data, 1);
	ft_parser(data, argv);
	ft_execute(data);
	ft_free(data);
	return (0);
}

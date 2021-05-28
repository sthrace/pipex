#include "pipex.h"

void	exec_child(t_pipe *data, int fd0, int fd1, int type)
{
	if (type == 1)
	{
		dup2(fd1, STDOUT_FILENO);
		dup2(data->fdin, STDIN_FILENO);
		close(data->fdin);
		close(fd0);
		close(fd1);
	}
	if (type == 2)
	{
		dup2(fd0, STDIN_FILENO);
		dup2(data->fdout, STDOUT_FILENO);
		close(data->fdout);
		close(fd0);
		close(fd1);
	}
	if (type == 3)
	{
		close(fd0);
		close(fd1);
	}
}

void	ft_execute(t_pipe *data)
{
	int	fd[2];
	int	pid_1;
	int	pid_2;

	if (pipe(fd) == -1)
		ft_exit(data, 0);
	pid_1 = fork();
	if (pid_1 < 0)
		ft_exit(data, 0);
	if (pid_1 == 0)
	{
		exec_child(data, fd[0], fd[1], 1);
		execve(data->argv_0[0], data->argv_0, data->environ);
	}
	pid_2 = fork();
	if (pid_2 < 0)
		ft_exit(data, 0);
	if (pid_2 == 0)
	{
		exec_child(data, fd[0], fd[1], 2);
		execve(data->argv_1[0], data->argv_1, data->environ);
	}
	exec_child(data, fd[0], fd[1], 3);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
}

void	ft_filecheck(t_pipe *data, char **arg, int i, int fd_test)
{
	char	*envpath;
	char	**paths;
	char	*file;

	while (data->environ[++i])
		if (!strncmp(data->environ[i], "PATH", 4))
			envpath = ft_substr(data->environ[i], 6, \
			ft_strlen(data->environ[i]));
	paths = ft_split(envpath, ':');
	free(envpath);
	i = -1;
	while (paths[++i])
	{
		file = ft_strjoin(paths[i], *arg);
		fd_test = open(file, O_RDONLY);
		if (fd_test != -1)
		{
			close(fd_test);
			free(*arg);
			*arg = ft_strdup(file);
			break ;
		}
		close(fd_test);
	}			
}

void	ft_parser(t_pipe *data, char **argv)
{
	char	*temp;

	data->fdin = open(argv[1], O_RDONLY);
	data->fdout = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->fdin == -1 || data->fdout == -1)
		ft_exit(data, 0);
	data->argv_0 = ft_split(argv[2], ' ');
	temp = ft_strdup(data->argv_0[0]);
	free(data->argv_0[0]);
	data->argv_0[0] = ft_strjoin("/", temp);
	ft_filecheck(data, &data->argv_0[0], -1, 0);
	data->argv_1 = ft_split(argv[3], ' ');
	free(temp);
	temp = ft_strdup(data->argv_1[0]);
	free(data->argv_1[0]);
	data->argv_1[0] = ft_strjoin("/", temp);
	free(temp);
	ft_filecheck(data, &data->argv_1[0], -1, 0);
}

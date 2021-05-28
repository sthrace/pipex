#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

# define RD 0
# define WR 1

typedef struct s_pipe
{
	char	**environ;
	int		argc_0;
	int		argc_1;
	char	**argv_0;
	char	**argv_1;
	int		fdin;
	int		fdout;
}				t_pipe;

// pipex.c //

void	ft_exit(t_pipe *data, int err);

// execution.c //

void	ft_parser(t_pipe *pipe, char **argv);
void	ft_execute(t_pipe *data);

#endif
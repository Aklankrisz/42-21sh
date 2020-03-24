#ifndef HALFSH_H

# define HALFSH_H

# include "ft_printf.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>

# define ARG_MAX 2097152

typedef struct		s_terminal
{
	struct termios	original;
	struct termios	shell;
	char		**env;
}			t_terminal;


int			print_char(int c);
int			config_terminal(int reset, t_terminal *term);
void			user_input(t_terminal *term);

#endif

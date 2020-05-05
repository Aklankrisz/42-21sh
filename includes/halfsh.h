#ifndef HALFSH_H

# define HALFSH_H

# include "ft_printf.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>

# define ARG_MAX 2097152
# define PROMPT "$>"

typedef struct		s_input
{
	char		string[ARG_MAX];
	int		index;
	size_t		line;
}			t_input;

typedef struct		s_terminal
{
	struct termios	original;
	struct termios	shell;
	struct winsize	size;
	char		**env;
	t_input		*in;
	t_list		*history;
	int		h_index;
}			t_terminal;

int			print_char(int c);
int			config_terminal(int reset, t_terminal *term);
void			config_signal(t_terminal *term);
void			user_input(t_terminal *term);
void			special_keys(t_terminal *term, int sum);
void			print_input(t_terminal *term);
void			arrow_navigation(t_terminal *term, int sum);
void			history_navigation(t_terminal *term, int sum);
void			ctrl_arrow_navigation(t_terminal *term, int sum);
void			navigate_right(t_terminal *term, size_t len, size_t cols);
void			navigate_left(t_terminal *term, size_t len, size_t cols);

#endif

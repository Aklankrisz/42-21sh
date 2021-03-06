/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:40:04 by vtran             #+#    #+#             */
/*   Updated: 2020/07/24 16:00:31 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_AST_H

# define PARSER_AST_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "lexer.h"

typedef struct				s_re_ag
{
	enum {
		REDIR,
		AGGRE
	}						e_flag;
	union
	{
		struct				s_re
		{
			int				*heredoc;
			char			*redir;
			char			*file;
		}					t_re;
		struct				s_ag
		{
			char			*n;
			char			*sign;
			char			*word;
		}					t_ag;
	}						node;
	struct s_re_ag			*next;
}							t_re_ag;

typedef struct				s_ast_n
{
	enum
	{
		FACTOR,
		EXPR
	}						e_node;
	union
	{
		struct				s_factor
		{
			enum
			{
				BUILDIN,
				EXEC
			}				e_factor;
			char			**cmds;
			t_re_ag			*list;
			char			*path_join;
		}					t_factor;
		struct				s_expr
		{
			struct s_ast_n	*left;
			struct s_ast_n	*right;
		}					t_expr;
	}						nodes;
}							t_ast_n;

typedef struct				s_parser_n
{
	enum
	{
		TOKEN,
		AST
	}						e_node;
	union
	{
		struct				s_t
		{
			t_token			*token;
		}					t_t;
		struct				s_a
		{
			t_ast_n			*ast_nodeobj;
		}					t_a;
	}						nodes;
}							t_parser_n;

typedef struct				s_parser_l
{
	t_parser_n				*parser_nodeobj;
	struct s_parser_l		*next;
}							t_parser_l;

typedef struct				s_ast
{
	t_ast_n					*parent;
	int						cmds;
	int						*pids;
	int						i;
	int						*pipe;
	int						in;
	int						out;
	int						err;
	int						rwfd;
	struct s_ast			*next;
}							t_ast;

typedef struct				s_free
{
	t_ast					*ast;
	t_parser_l				*parser;
	t_lexer					*lexer;
}							t_free;

t_ast_n						*create_factor(char **cmnd, t_re_ag *list);
t_ast_n						*create_expression(t_ast_n *left, \
							t_ast_n *right);
void						helper_dup(t_ast **ast, t_ast_n *obj, \
							int pipe_in);
void						helper_close(t_ast_n *obj, t_ast **ast);
void						visit_exec(t_ast_n *obj, t_ast **ast, \
							t_env *env);
void						visit_re_ag(t_ast_n *obj, t_ast **ast);
void						visit_expression(t_ast_n *obj, \
							t_ast **ast, t_terminal *term, t_free *willy);
void						add_node_to_parser_node_list(t_parser_l
							**list, t_parser_n *ast_node, \
							t_parser_n *token_node);
t_ast						*create_ast_list(t_parser_l *list);
void						execute_ast(t_ast *a, t_terminal *t, t_free *willy);
t_re_ag						*tokens_to_redirection(t_token *h, \
							t_token *l, t_terminal *t);
void						free_ast(t_ast *list);
void						free_parser(t_parser_l *list);
void						free_tokens(t_token *list);
t_ast						*init_ast(void);
void						buildin_factor(t_ast_n *obj, \
							t_ast **ast, t_terminal *term, t_free *willy);
char						*value_lookup(t_list *env, char *key);
int							buildin_cd(t_env *env, char **args);
void						unset_key(t_list *env, char *key);
void						set_key(t_list *env, char *k, char *v);
int							buildin_env(char **env);
int							buildin_unsetenv(t_terminal *term, char **args);
int							buildin_setenv(t_terminal *term, char **args);
void						cmd_not_found(char *cmd);
void						buildin_echo(char **obj);
void						n_redirection(t_ast **ast, char *file, char *redir);
void						and_greater(t_ast **ast, char *file);
void						greater_and_double(t_ast **ast, \
							char *file, char *redir);
void						less_than(t_ast **ast, char *file);
void						heredoc(t_ast **ast, t_re_ag *node);
void						less_greater_than(t_ast **ast, char *file);
t_free						*init_willy(t_lexer *lexer, t_ast *ast, \
							t_parser_l *parser);
void						free_willy(t_free *willy, t_terminal *term);
char						*if_slash(char *name);
#endif

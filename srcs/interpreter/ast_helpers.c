#include "parser_ast.h"

void			helper_dup(t_ast **ast, t_ast_node *obj, int pipe_in)
{
	dup2((*ast)->in, 0);
	if ((*ast)->parent->node == 1 && obj
	!= (*ast)->parent->nodes.expr.right)
		dup2(pipe_in, 1);
	else
		dup2((*ast)->out, 1);
}

//lisää vaihtoehtoja..

void			helper_close(t_ast_node *obj, t_ast **ast)
{
	t_redirection_aggregation *node;
	
	node = obj->nodes.factor.list;
	if (node && node->flag == 0)
	{
		if (node->token.redirection.redir[0] == '<')
			close((*ast)->in);
	}
}

//helper aggreagation ?

// void			helper_aggregation(t_ast **ast)
// {

// }
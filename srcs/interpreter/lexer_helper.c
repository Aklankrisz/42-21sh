/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:53:54 by hege              #+#    #+#             */
/*   Updated: 2020/07/22 23:54:03 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		add_token(t_token **tokens, t_token *new)
{
	t_token *tmp;

	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:33 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 23:03:14 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"
#include "parser_ast.h"

/*
** Deletes character from the command by shifting bytes after the index
** to the left once. The byte after the last character is initialized
** to zero after memmove.
*/

static void	delete_char(t_terminal *term)
{
	size_t	len;

	if (term->in->index > 0)
	{
		len = ft_strlen(term->in->string);
		term->in->index--;
		ft_memmove(term->in->string + term->in->index, \
		term->in->string + term->in->index + 1, \
		ft_strlen(term->in->string + term->in->index + 1));
		term->in->string[len - 1] = 0;
	}
}

/*
** Chooses right action by comparing sum and different
** definitions from keyboard.h file.
*/

void		search_action(t_terminal *term, int sum)
{
	if (sum == LEFT || sum == RIGHT \
	|| sum == CTRL_LEFT || sum == CTRL_RIGHT)
		cursor_movement_1(term, sum);
	else if (sum == CTRL_UP || sum == CTRL_DOWN \
	|| sum == HOME || sum == END)
		cursor_movement_2(term, sum);
	else if (sum == UP || sum == DOWN)
		browse_history(term, sum);
	else if (sum == COPY || sum == PASTE)
		clipboard(term, sum);
	else if (sum == BACK)
		delete_char(term);
}

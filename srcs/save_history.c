/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:50:52 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 09:59:03 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Opens file defined in the halfsh.h file and appends current history
** in to the file using add_history function. If the file does not exist,
** Program will create one with appropriate permissions.
*/

void		save_history(t_terminal *term)
{
	int		fd;
	t_list	*cur_list;
	int		count;

	fd = open(CMD_FILE, O_WRONLY|O_CREAT, 0666);
	if (fd == -1)
		return ;
	cur_list = term->history;
	count = 0;
	while (cur_list && count < FILE_LEN)
	{
		ft_putendl_fd(cur_list->content, fd);
		cur_list = cur_list->next;
		count++;
	}
	close(fd);
}

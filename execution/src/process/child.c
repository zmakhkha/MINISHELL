/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-fil <ayel-fil@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 06:13:41 by ayel-fil          #+#    #+#             */
/*   Updated: 2023/06/19 06:14:37 by ayel-fil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	ft_child_process(t_cmd *cmd)
{
	if (execve(cmd->path_cmd, cmd->args, cmd->env) == -1)
	{
		ft_perror(*cmd->args,CNF);
		return (127);
	}
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-fil <ayel-fil@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:20:43 by ayel-fil          #+#    #+#             */
/*   Updated: 2023/06/11 16:05:47 by ayel-fil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

bool	is_builtin(char *command)
{
	if (!ft_strcmpl(command, "echo") ||
		!ft_strcmp(command, "cd") ||
		!ft_strcmpl(command, "pwd") ||
		!ft_strcmp(command, "export") ||
		!ft_strcmp(command, "unset") ||
		!ft_strcmpl(command, "env") ||
		!ft_strcmp(command, "exit"))
	{
		return (true);
	}
	return (false);
}

int	execute_builtin(char **list, t_env *env)
{
	ft_p2darray(list, 2);
	if (list)
	{
		if (!ft_strcmpl(list[0], "echo"))
			return (execute_echo(list));
		else if (!ft_strcmp(list[0], "cd"))
			return (execute_cd(list, env));
		else if (!ft_strcmpl(list[0], "pwd"))
			return (execute_pwd(env));
		else if (!ft_strcmp(list[0], "export"))
			execute_export(list, &env);
		// else if (ft_strcmp(list->str, "unset"))
		// 	execute_unset(list, env);
		else if (!ft_strcmpl(list[0], "env"))
			return (execute_env(&env));
		// else if (!ft_strcmp(list->str, "exit"))
		// 	execute_exit(list);
	}
	return (EXIT_FAILURE);
}
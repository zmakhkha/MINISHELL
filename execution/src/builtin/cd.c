/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-fil <ayel-fil@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:42:09 by ayel-fil          #+#    #+#             */
/*   Updated: 2023/06/11 13:01:00 by ayel-fil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	execute_cd(char **cmd, t_env *env)
{
	if (cmd[1] == NULL)
	{
		char *home_dir = get_value("HOME", env);
		if (home_dir == NULL)
		{
			ft_perror("cd", "HOME not set");
			return (1);
		}

		if (chdir(home_dir) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (chdir(cmd[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}

	return (0);
}
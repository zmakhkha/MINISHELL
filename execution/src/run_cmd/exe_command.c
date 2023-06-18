/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-fil <ayel-fil@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:16:02 by ayel-fil          #+#    #+#             */
/*   Updated: 2023/06/18 16:11:50 by ayel-fil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

char	**get_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	ft_putendl_fd("Path env is not set",ER);
	return (0);
}

t_cmd	ft_init_cmd(char *args, char **env)
{
	t_cmd	cmd;

	cmd.args = ft_split(args, ' ');
	cmd.name = cmd.args[0];
	cmd.env = env;
	cmd.paths = get_path(env);
	return (cmd);
}

char	*set_cmd_path(t_cmd *cmd)
{
	char	*path;
	char	*temp_path;
	int		i;

	i = 0;
	cmd->name = ft_strjoin("/", cmd->name);
	while (cmd->paths[i])
	{
		temp_path = ft_strjoin(cmd->paths[i], cmd->name);
		if (access(temp_path, X_OK) == 0)
		{
			path = ft_strdup(temp_path);
			free(temp_path);
			free(cmd->name);
			return path;
		}
		free(temp_path);
		i++;
	}
	ft_error(CNF, cmd->name, 1);//TODO gad l9wali : check path before child process ??
	//!WAAAAARNIIIIIIING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	free(cmd->name);
	
	return NULL;
}


bool	ft_check_relative_or_binary(t_cmd *cmd)
{
	if (ft_strchr(cmd->name, '/'))
		return (true);
	return (false);
}
int execute_command(char *args, t_env *env)
{
    t_cmd cmd;
    pid_t pid;
    int status;

    cmd = ft_init_cmd(args, list_to_array(env));
    pid = fork();
    if (pid == -1)
    {
       ft_perror("fork","Fork failed");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        status = ft_child_process(&cmd);
        exit(status);
    }
        waitpid(pid, &status, 0);
        //!! free_cmd(&cmd);
        return status;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-fil <ayel-fil@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 05:25:46 by ayel-fil          #+#    #+#             */
/*   Updated: 2023/06/21 05:59:49 by ayel-fil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

void	free_env_node(t_env *node)
{
	if (node == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
void	unset_env(const char *key, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			free_env_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
int	execute_unset(char **list, t_env **env_list)
{
	int	i;

	i = 1;
	if (!list[0])
		return (EXIT_SUCCESS);
	while (list[i])
		unset_env(list[i++], env_list);
	return (EXIT_FAILURE);
}

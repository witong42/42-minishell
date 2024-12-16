/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:25:07 by witong            #+#    #+#             */
/*   Updated: 2024/12/16 16:37:08 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir *create_redir(t_token *token)
{
	t_redir *new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = token->type;
	new_redir->file = ft_strdup(token->value);
	if (!new_redir->file)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	return (new_redir);
}

void redir_add_back(t_redir **redirs, t_redir *new_redir)
{
	t_redir *redir;

	if (!redirs || !new_redir)
		return ;
	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	redir = *redirs;
	while (redir->next)
		redir = redir->next;
	redir->next = new_redir;
}

void	print_table(t_cmd *cmd)
{
	int	i;
	int	j;
	t_cmd	*current;

	j = 0;
	current = cmd;
	while (current)
	{
		i = 0;
		printf("Command[%d]:\n", j);
		while (current->full_cmd[i])
		{
			printf("  Arg[%d]: %s\n", i, current->full_cmd[i]);
			i++;
		}
		printf("  Arg[%d]: %s\n", i, current->full_cmd[i]);
		current = current->next;
		j++;
	}
}

void print_redirs(t_redir *redirs)
{
	t_redir *current = redirs;

	while (current)
	{
		printf("Redirection type: %d, file: %s\n", current->type, current->file);
		current = current->next;
	}
}
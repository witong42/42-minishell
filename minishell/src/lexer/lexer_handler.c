/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:21 by witong            #+#    #+#             */
/*   Updated: 2024/12/14 15:02:04 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_double_ops(const char *line, int *i, t_token **tokens)
{
	char *value;
	t_tok_type type;

	type = UNKNOWN;
	if (line[(*i) + 1])
		type = check_double_ops(line[*i], line[(*i) + 1]);
	if (type != UNKNOWN)
	{
		value = ft_substr(line, *i, 2);
		if(!value)
			return ;
		token_add_back(tokens, create_token(type, value));
		*i += 2;
	}
}

void handle_redirection(const char *line, int *i, t_token **tokens)
{
	char *value;
	t_tok_type type;

	type = check_redirection(line[*i]);
	value = ft_substr(line, *i, 1);
	if(!value)
		return ;
	token_add_back(tokens, create_token(type, value));
	(*i)++;
}

void handle_quotes(const char *line, int *i, t_token **tokens)
{
	char *value;

	if (line[*i] == '\'')
	{
		value = extract_single_quote(line, i, tokens);
		if (!value)
			return ;
		token_add_back(tokens, create_token(SINGLEQ, value));
	}
	else if (line[*i] == '\"')
	{
		value = extract_double_quote(line, i, tokens);
		if (!value)
			return ;
		token_add_back(tokens, create_token(DOUBLEQ, value));
	}
}

void handle_dollar(const char *line, int *i, t_token **tokens)
{
	char *value;
	t_tok_type	type;

	value = extract_dollar(line, i);
	if (!value)
		return ;
	if (ft_strncmp(value, "$", 1) == 0)
		type = WORD;
	else
		type = DOLLAR;
	token_add_back(tokens, create_token(type, value));
}

void handle_word(const char *line, int *i, t_token **tokens)
{
	char *value;

	value = extract_word(line, i);
	if(!value)
		return ;
	token_add_back(tokens, create_token(WORD, value));
}

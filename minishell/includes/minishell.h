#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "lexer.h"
# include "parser.h"
# include "expand.h"
// # include "exec.h"
// # include "builtins.h"
# include "utils.h"

typedef struct s_shell t_shell;
typedef struct s_token t_token;
typedef enum e_type t_type;
typedef struct s_clean t_clean;

/* redirections structure */
typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;
}			t_redir;

/* commands chained list */
typedef struct s_cmd
{
	char			**full_cmd;
	int				infile; // OU CHAR * // A DETERMINER
	int				outfile; // OU CHAR * // A DETERMINER
	bool			is_quote;
	char			*limiter;
	int				*pipe;
	pid_t			*pids;
	struct s_redir	*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}			t_cmd;

/* global data structure */
typedef struct s_shell
{
	int		argc;
	int		exit_status;
	char	**argv;
	char	**envp;
	char	*input;
	t_token	*token;
	t_cmd	*cmd;
	t_clean	*clean;
}			t_shell;

#endif

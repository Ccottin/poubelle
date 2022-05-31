#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

typedef enum	e_token_type {
	REDIR_ADD,
	REDIR_LIM,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	QUOTE,
	S_QUOTE,
	WHITE_SPACE,
	STR,
	FLAG,
	CMD
} t_token_type;

typedef struct	s_token {
	char 	*token;
	uint32_t	size;
	t_token_type	type;
}	t_token;

typedef struct	s_lexed {
	t_token	*tokens;
	uint32_t	size;
	}	t_lexed;

typedef struct	s_env {
	t_token	*tab;
	t_lexed	*lexed;
	}	t_env;
	
#endif 

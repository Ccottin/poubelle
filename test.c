#include "header.h"

int	ft_cpy(char *s1, char **s2, int size)
{
	int		i;

	*s2 = calloc(size + 1, 1);
	if (!*s2)
		return (-1);
	i = 0;
	while (s1[i])
	{
		(*s2)[i] = s1[i];
		i++;
	}
	return (0);
}

int	set_token_list(int i, t_token *var)
{
	if (i == 0)
	{
		if (ft_cpy(">>", &(var->token), 2) == -1)
			return (-1);
		var->size = 2;
		var->type = REDIR_ADD;
	}
	if (i == 1)
	{
		if (ft_cpy("<<", &(var->token), 2) == -1)
			return (-1);
		var->size = 2;
		var->type = REDIR_LIM;
	}
	if (i == 2)
	{
		if (ft_cpy("<", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = REDIR_IN;
	}
	if (i == 3)
	{
		if (ft_cpy(">", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = REDIR_OUT;
	}
	if (i == 4)
	{
		if (ft_cpy("|", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = PIPE;
	}
/*	if (i == 5)
	{
		if (ft_cpy("\"", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = QUOTE;
	}
	if (i == 6)
	{
		if (ft_cpy("'", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = S_QUOTE;
	}*/
	if (i == 5)
	{
		if (ft_cpy(" ", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = WHITE_SPACE;
	}
	if (i == 6)
	{
		if (ft_cpy("\t", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = WHITE_SPACE;
	}
	if (i == 7)
	{
		if (ft_cpy("\n", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = WHITE_SPACE;
	}
	if (i == 8)
	{
		if (ft_cpy("\v", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = WHITE_SPACE;
	}
	if (i == 9)
	{
		if (ft_cpy("\f", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = WHITE_SPACE;
	}
	if (i == 10)
	{
		if (ft_cpy("\r", &(var->token), 1) == -1)
			return (-1);
		var->size = 1;
		var->type = WHITE_SPACE;
	}
	return (0);
}

int	token_init(t_env *env)
{
	int	i;
	t_token	var;
	
	env->tab = calloc(sizeof(t_token) * 10 + 1, 1); //pense a switch en ftcalloc
	if (!env->tab)
		return (-1);
	i = 0;
	while (i < 10)
	{
		if (set_token_list(i, &var) == -1)
			return (-1);
		env->tab[i] = var;
		i++;
	}
//	i = 0;
//	while (i < 13)
//	{
//		printf("%s, %d, %d = %d \n", env->tab[i].token, env->tab[i].size, env->tab[i].type, i);
//		i++;
//	}
	return (0);
}

int	get_lexed(t_env *env, char *temp, t_token_type type, int size)
{
	static int	i = 0;

	env->lexed->tokens[i].token = temp; //ya un monde ou ca marche pas et faut calloc ou copy ou autre
	env->lexed->tokens[i].type = type;
	env->lexed->tokens[i].size = size;
	i++;
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i == 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (s1[i] == 0 && s2[i] == 0)
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_temp(char *temp, t_env *env, char next)
{
	int	i;

	i = 0;
	if (temp[i] == '\"' || temp[i] == '\'')
	{
		while (temp[i])
			i++;
		if (temp[i] == '\"' || temp[i] == '\'')
			return (get_lexed(env, temp, STR, ft_strlen(temp))); //yaura surement besoin de se prendre la tete de ouf ici mais pr l instant pas
	}
	i = 0;
	while (i < 10)
	{
		if (ft_strcmp(temp, env->tab[i].token) == 1)
			return (get_lexed(env, temp, env->tab[i].type, env->tab[i].size));
		i++;
	}
	i = 0;
	if (next == '\"' || next == '\'' || next == WHITE_SPACE || next == '|' || next == '<' || next == '>')
	{
		if (temp[i] == '-')
			return (get_lexed(env, temp, FLAG, ft_strlen(temp)));
		else
			return (get_lexed(env, temp, CMD, ft_strlen(temp)));
	}
	return (0);
	//renvoie 1 si un token est lexeeeeeeee
}

int	lexer(char *line, t_env *env)
{
	int	i;
	int	y;
	char	*temp;
	int	s_quot;
	int	quot;


	i = 0;
	y = 0;
	s_quot = 0;
	quot = 0;
	temp = calloc(100, 1); //make it dynamiq
	if (!temp)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\'')
			s_quot++;
		if (line[i] == '\"')
			quot++;
		temp[y] = line[i];
		if (line[i + 1] == '\"' || line[i + 1] == '\'' || line[i + 1] == WHITE_SPACE || line[i + 1] == '|' || line[i + 1] == '<'
			|| line[i + 1] == '>')
			if (check_temp(temp, env, line[i + 1]) == 1)
			{
				y = 0;
				while (y < 100)
				{
					temp[y] = 0;
					y++;
				}
				y = -1;
			}
		i++;
		y++;
	}
	return (0);
}

int	init(t_env *env)
{
	env->lexed = calloc(sizeof(t_token) * 100, 1); //make it dynamiq
	if (!env->lexed)
		return (-1);
}

void	ft_return(t_env *env)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (env->tab[i].token)
			free(env->tab[i].token);
		i++;
	}
	free(env->tab);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (token_init(&env) == -1)
		return (-1);
	if (init(&env) == -1)
		return (-1);
	if (lexer(av[1], &env) == -1)
	{
		write(1, "Error.\n", 7);
		return (-1);
	}
	int			i;
	i  = 0;
	while (env.lexed->tokens[i].size != 0)
	{
		printf("%s, %d, %d = %d \n", env.lexed->tokens[i].token, env.lexed->tokens[i].size, env.lexed->tokens[i].type, i);
		i++;
	}
	ft_return(&env);
	return (0);
}

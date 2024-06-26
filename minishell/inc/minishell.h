/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:10:08 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/28 15:44:57 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int				g_minishell;

# define MAX_COMMAND_LENGTH 1024

enum					e_exceptions
{
	ERROR,
	SUCCESS,
};

typedef struct s_token
{
	char				*content;
	struct s_token		*next;
}						t_token;

typedef struct s_data
{
	char				**full_cmd;
	char				*path;
	int					in_fd;
	int					out_fd;
	int					redirect_in;
	int					redirect_out;
	int					append;
	char				*in_path;
	char				*out_path;
	int					use_heredoc;
	char				*heredoc_delimiter;
	int					original_stdout;
	int					original_stdin;
	struct s_data		*next;

}						t_data;

typedef struct s_env_var
{
	char				*content;
	char				*var_name;
	bool				is_exported;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_shell
{
	char				**env_vars;
	t_env_var			*env_list;
	char				*path;
	char				*cwd;
	bool				exit;
	int					ret;
	int					i;
	int					word_len;
	char				*current_word;
}						t_shell;

void					init_shell(t_shell *shell, char **envp);
void					free_env_list(t_env_var *env_list);
void					init_env_list(t_shell *shell, char **envp);
t_env_var				*create_env_var(char *env_var_str);
t_env_var				*copy_env_to_struct(char **envp);
void					add_node(t_env_var **head, char *content);
int						is_node(char *str, t_env_var **head);
char					**copy_env(char **envp);
char					*get_env(t_env_var *head, char *var_name);
char					*get_path_var(char **envp);
void					update_env(t_env_var **head, char *var_name,
							char *new_content, t_shell *shell);
void					create_env(t_env_var **head, char *var_name,
							char *content, t_shell *shell);
void					delete_env(t_env_var **head, char *var_name,
							t_shell *shell);
void					update_shlvl(t_shell *shell);
void					update_env_vars(t_shell *shell);
char					**env_list_to_array(t_env_var *env_list);
t_token					*tokenize(const char *input, t_shell *shell);
char					*extract_var_name(const char *input);
int						handle_dollar_sign(const char *input, t_shell *shell);
int						handle_quotes(const char *input, t_shell *shell);
int						handle_character(const char *input, t_token **tokens,
							t_shell *shell);
t_token					*create_token(char *content);
void					add_token_to_list(t_token **token_list,
							t_token *new_token);
void					finalize_word(t_shell *shell, t_token **tokens);
int						is_special_char(char c);
int						is_valid_var_char(char c);
t_data					*initialize_command(void);
void					handle_special_tokens(t_token **token,
							t_data *current_command);
t_data					*create_command(char **args, int arg_count);
int						validate_command(t_data *commands);

t_data					*parse_tokens(t_token *tokens, t_data *head,
							t_data *current_command, int arg_cnt);
t_token					*parse_redirection(t_data *current_command,
							t_token *tokens);

void					exec_pipeline(t_data *commands, t_shell *shell);
char					*find_command_path(char *cmd, char *path_var);
void					execute_command(t_data *commands, t_shell *shell,
							char *cmd_path);
char					*exec_binary(char *cmd, char *path_var);
void					exec_command(t_data *commands, t_shell *shell);
void					executor(t_data *commands, t_shell *shell);
char					*get_path_from_env_var(t_env_var *env_var);
void					free_tokens(t_token *tokens);
void					free_commands(t_data *commands);
void					free_str_array(char **array);
void					free_shell(t_shell *shell);
int						is_builtin(t_data *data);
int						builtin(char *cmd, char **args, t_shell *shell);
void					ms_echo(char **words);
int						ms_cd(char **words, t_shell *shell);
int						ms_exit(t_shell *shell, char **prompt);
int						ms_env(t_env_var *env);
int						ms_pwd(void);
int						ms_unset(t_env_var **env, char **args, t_shell *shell);
int						ms_export(t_env_var **env, char **args, t_shell *shell);
void					new_prompt(int sig);
void					sigint_handler(int sig);
void					sigquit_handler(int sig);
void					setup_signals(int sig);
int						is_redir_operator(char *token_content);
void					write_error(const char *msg, const char *filename);
int						redirect_output(t_data *data);
int						redirect_input(t_data *data);
void					child_redir(t_data *data, t_shell *shell, char **cmd);
void					handle_here_doc(const char *delimiter);
void					setup_redir(t_data *commands);
void					restore_redir(t_data *commands);
void					exec_cmd_path(t_data *commands, t_shell *shell,
							char *cmd_path);
#endif

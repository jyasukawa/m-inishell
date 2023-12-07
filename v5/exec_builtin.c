#include "minishell.h"

static void	ft_select_and_exec_cmd(char *cmd, char **args, t_shell *shell)
{
	g_exit_status = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args);
	// else if (ft_strcmp(cmd, "cd") == 0)
	// 	ft_cd();
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(shell);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	ft_export();
	// else if (ft_strcmp(cmd, "unset") == 0)
	// 	ft_unset();
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(args, shell);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(args, shell);
}

static void	ft_reset_std_fd(t_shell *shell)
{
	if (dup2(shell->std_fd[0], STDIN_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (dup2(shell->std_fd[1], STDOUT_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(shell->std_fd[0]) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(shell->std_fd[1]) == -1)
		ft_free_all_and_exit(shell, 1);
}

static void	ft_store_std_fd(t_shell *shell)
{
	shell->std_fd[0] = dup(STDIN_FILENO);
	if (shell->std_fd[0] == -1)
		ft_free_all_and_exit(shell, 1);
	shell->std_fd[1] = dup(STDOUT_FILENO);
	if (shell->std_fd[1] == -1)
		ft_free_all_and_exit(shell, 1);
}

void	ft_exec_builtin(t_node node, t_shell *shell)
{
	ft_store_std_fd(shell);
	ft_prepare_redirects(node, shell);
	if (shell->single_node_builtin_error != -1)
		ft_select_and_exec_cmd(node.args[0], node.args + 1, shell);
	ft_reset_std_fd(shell);
}

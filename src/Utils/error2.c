void    error_too_many_arguments(const char *cmd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd((char *)cmd, STDERR_FILENO);
    ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
}
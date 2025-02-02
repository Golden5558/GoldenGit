/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:10:46 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/02 18:14:43 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	for (int i = 0; envp[i] != NULL; i++)
// 	{
// 		printf("%s\n", envp[i]);
// 	}
// 	return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"



// int	main(int argc, char **argv)
// {
// 	char	*limiter;
// 	char	*line;


// 	if (argc < 3)
// 		return (1);
// 	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
// 		return (1);
// 	limiter = ft_strjoin(argv[2], "\n");
// 	ft_putstr_fd("pipe heredoc>", 1);
// 	while (1)
// 	{
// 		line = get_next_line(1);
// 		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			free(line);
// 			free(limiter);
// 			break;
// 		}
// 		if (line)
// 			ft_putstr_fd("pipe heredoc>", 1);
// 		free(line);
// 	}
// }

void	close_all_pipefd(t_file *file, int to_close)
{
	int	i;
	
	i = 0;
	if (to_close >= 0)
		close(to_close);
	while (i < file->nb_cmd - 1)
	{
		close(file->pipefd[i][0]);
		close(file->pipefd[i][1]);
		i++;
	}
}

void	error_exit(char *msg, t_file *file, t_cmd **list_cmd)
{
	ft_lstclear(list_cmd);
	if (file)
	{
		if (file->pids)
			free(file->pids);
		if (file->pipefd)
			free(file->pipefd);
	}
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

static void	get_command_amount(int argc, char **argv, char **envp, t_file *file)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_putstr_fd("Too few arguments\n", 2);
		exit (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		file->nb_cmd = argc - 4;
		file->start_cmd = 3;
		file->here_doc = 1;
	}
	else
	{
		file->nb_cmd = argc - 3;
		file->start_cmd = 2;
	}
	file->argv = argv;
	file->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	t_cmd	*list_cmd;
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];

	list_cmd = NULL;
	ft_memset(&file, 0, sizeof(t_file));
	get_command_amount(argc, argv, envp, &file);
    pars_cmds(argv, envp, &file, &list_cmd);
    open_files(argv, argc, &file, &list_cmd);
    if (pipe(pipefd) == -1)
        error_exit("Pipe creation failed\n", &file, &list_cmd);
	pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (pid1 == 0)
	{
		dup2(file.infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(file.infile);
		close(file.outfile);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(list_cmd->path, list_cmd->cmd_args, envp);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		list_cmd = list_cmd->next;
		dup2(pipefd[0], STDIN_FILENO);
		dup2(file.outfile, STDOUT_FILENO);
		close(file.infile);
		close(file.outfile);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(list_cmd->path, list_cmd->cmd_args, envp);
	}
    close(file.infile);
    close(file.outfile);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    ft_lstclear(&list_cmd);
    return (0);
}














/*
// Fonction d'erreur pour simplifier la gestion
void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s infile \"cmd1\" \"cmd2\" outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 1. Ouvrir infile en lecture
    int infile = open(argv[1], O_RDONLY);
    if (infile < 0)
        error_exit("Erreur lors de l'ouverture de infile");

    // 2. Ouvrir outfile en écriture (création/troncature)
    int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0) {
        close(infile);
        error_exit("Erreur lors de l'ouverture de outfile");
    }

    // 3. Créer un pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        close(infile);
        close(outfile);
        error_exit("Erreur lors de la création du pipe");
    }

    // 4. Forker le premier processus pour cmd1
    pid_t pid1 = fork();
    if (pid1 < 0) {
        close(infile);
        close(outfile);
        close(pipefd[0]);
        close(pipefd[1]);
        error_exit("Erreur lors du fork pour cmd1");
    }

    if (pid1 == 0) {
        // --- Processus Fils 1 : cmd1 ---
        
        // Rediriger stdin depuis infile
        if (dup2(infile, STDIN_FILENO) == -1)
            error_exit("Erreur dup2 infile");

        // Rediriger stdout vers le pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            error_exit("Erreur dup2 pipefd[1]");

        // Fermer les descripteurs inutilisés
        close(pipefd[0]); // Fermer l'extrémité de lecture du pipe
        close(pipefd[1]); // Fermer l'extrémité d'écriture du pipe (déjà dupliquée)
        close(infile);    // Fermer infile
        close(outfile);   // Fermer outfile (non utilisé dans ce processus)

        // Préparer les arguments pour execve
        char *cmd1 = "/bin/ls"; // Chemin complet de cmd1 (à ajuster)
        char *cmd1_args[] = { "ls", "-l", NULL };

        // Exécuter cmd1
        execve(cmd1, cmd1_args, envp);

        // Si execve échoue
        perror("Erreur execve cmd1");
        exit(EXIT_FAILURE);
    }

    // 5. Forker le deuxième processus pour cmd2
    pid_t pid2 = fork();
    if (pid2 < 0) {
        close(infile);
        close(outfile);
        close(pipefd[0]);
        close(pipefd[1]);
        error_exit("Erreur lors du fork pour cmd2");
    }

    if (pid2 == 0) {
        // --- Processus Fils 2 : cmd2 ---
        
        // Rediriger stdin depuis le pipe
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
            error_exit("Erreur dup2 pipefd[0]");

        // Rediriger stdout vers outfile
        if (dup2(outfile, STDOUT_FILENO) == -1)
            error_exit("Erreur dup2 outfile");

        // Fermer les descripteurs inutilisés
        close(pipefd[0]); // Fermer l'extrémité de lecture du pipe (déjà dupliquée)
        close(pipefd[1]); // Fermer l'extrémité d'écriture du pipe
        close(infile);    // Fermer infile (non utilisé dans ce processus)
        close(outfile);   // Fermer outfile

        // Préparer les arguments pour execve
        char *cmd2 = "/usr/bin/wc"; // Chemin complet de cmd2 (à ajuster)
        char *cmd2_args[] = { "wc", "-l", NULL };

        // Exécuter cmd2
        execve(cmd2, cmd2_args, envp);

        // Si execve échoue
        perror("Erreur execve cmd2");
        exit(EXIT_FAILURE);
    }

    // 6. Processus Parent
    
    // Fermer les descripteurs de fichier inutilisés
    close(pipefd[0]); // Fermer l'extrémité de lecture du pipe
    close(pipefd[1]); // Fermer l'extrémité d'écriture du pipe
    close(infile);    // Fermer infile
    close(outfile);   // Fermer outfile

    // Attendre la terminaison des processus fils
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
*/
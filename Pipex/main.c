/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:10:46 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/29 10:37:17 by nberthal         ###   ########.fr       */
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



int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	buf[2];
	char	*line;


	i = 0;
	if (argc != 3)
		return (1);
	if (ft_strcmp(argv[1], "here_doc") != 0)
		return (1);
	while (1)
	{
		read(0, buf, 1);
		buf[1] = '\0';
		
	}
}














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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:02:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/09/08 13:35:40 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

// affiche 'A' en haut a gauche ET en bas a droite
void	ft_put_corner(int x, int y, int colomn, int line)
{
	if (colomn == 1 && line == 1)
		ft_putchar('A');
	if ((colomn == x && line == y) && (x > 1 && y > 1))
		ft_putchar('A');
}

// affiche 'C' en haut a droite ET en bas a gauche
void	ft_put_corner2(int x, int y, int colomn, int line)
{
	if ((colomn == x && line == 1) && (x > 1))
		ft_putchar('C');
	if ((colomn == 1 && line == y) && (y > 1))
		ft_putchar('C');
}

// affiche 'B' sur la premiere et derniere ligne
// ET sur la premiere et derniere colonne
void	ft_put_border(int x, int y, int colomn, int line)
{
	if ((colomn > 1 && colomn < x) && (line == 1 || line == y))
		ft_putchar('B');
	if ((line > 1 && line < y) && (colomn == 1 || colomn == x))
		ft_putchar('B');
}

// affiche ' ' (espace) entre la premiere et derniere colonne
// ET entre la premiere et derniere ligne 
void	ft_put_space(int x, int y, int colomn, int line)
{
	if ((colomn > 1 && colomn < x) && (line > 1 && line < y))
		ft_putchar(' ');
}

// le premier while parcours les lignes
// le deuxieme while parcours les colonnes
void	rush(int x, int y)
{
	int	colomn;
	int	line;

	line = 1;
	while (line <= y)
	{
		colomn = 1;
		while (colomn <= x)
		{
			ft_put_corner(x, y, colomn, line);
			ft_put_corner2(x, y, colomn, line);
			ft_put_border(x, y, colomn, line);
			ft_put_space(x, y, colomn, line);
			colomn++;
		}
		ft_putchar('\n');
		line++;
	}
}

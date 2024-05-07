/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:34:26 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/23 18:45:05 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// matrix zwalnia pamiec dla tablicy, ktora stworzylem podczas pracy
// funkcji ft_split. Dlatego w mainie jest stack_init(&a, argv + 1, argc == 2)
// Ostatni warunek argc == 2, sprawdza wlasnie czy mam
// do czynienia z przypadkiem, w ktorym wprowadzilismy tylko jeden argument
// do programu. A jak jest argc == 2, to uzywam ft_split, czyli
// zawsze jak jest argc == 2, to tworze nowa tabele w ft_split.

// wytlumaczenie x = -1: w main.c inicjuje stack_init(&a, argv + 1, argc == 2)
// &a - to adres stosu
// argv + 1 - przesuwa mnie od razu na pozycje gdzie jest pierwsza liczba
// z pominieciem nazwy programu (przy argv) lub '\0' w przypadku splita
// (ktory jest defacto sztucznym argv)
// argc == 2 - ustawia warunek dla flagi, ktora sprawdza prawdziwosc tego stwierdzenia
//
// i teraz w funkcji stack_init, *argv[] to pointer i wskazuje mi na drugie miejsce
// w tablicy (ktora stworzyl ft_split) i oznacza je jako 0, chociaz tak naprawde jest to pozycja 1.
// Dlatego jak zwalniam pamiec w matrix_free, x musi byc x = -1. Bo miejsce, ktore bylo na pozycji 0 po
// wykonaniu splita, teraz jest na pozycji -1. Bardzo to zawile, ale dziala to mniej wiecej tak.

void matrix_free (char *argv[])
{
	int x;

	x = -1;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[x])
		free(argv[x++]);
	free(argv - 1); // argv wskazuje na pierwszy element tablicy, a nie na sama tablice. dlatego tu jest -1 (nie wiem czy to ma sens?)
}

// Uwalniam pamiec w stosie a. Jezeli stack jest NULL to zwracam 0.
// W innym przypadku do zmiennej current przypisuje wskaznik na stos a.
// Dopoki nie dojde do konca stosu to w kazdej petli do zmiennej
// tymczasowej tmp przypisuje wartosc kolejnego miejsca w stacku.
// Uwalniam pamiec w aktualnym miejscu w stacku. Przypisuje current
// wartosc z tmp. I tak do konca stosu.

void stack_free(t_stack **stack)
{
	t_stack *tmp;
	t_stack *current;

	if (stack == NULL)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next; // przypisuje current nastepne miejsce w stacku
		free(current); // uwalniam pamiec z aktualnego miejsca
		current = tmp; // przypisuje current wartosc z tmp
	}
	*stack = NULL;
}

// wypisuje blad i jesli argc == 2 (czyli kiedy wprowadzilem tylko 1 argument, np. "1 34 -65" lub 42) to uwalniam pamiec w zapisanej przez split tablicy

void error_free(t_stack **a, char *argv[], bool flag_argc_2)
{
	stack_free(a); // skoro jest blad to musze uwolnic pamiec dla stosu a
	if (flag_argc_2) // jezeli argc == 2 (bo taki warunek "zaszylem" w tej fladze) to zwalniam pamiec dla tablicy, ktora stworzylem za pomoca ft_split
		matrix_free(argv);
	write (2, "Error\n", 6);
	exit(1);
}

// error_syntax obsluguje bledy jak niedozwolone znaki itd.

int error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-' || (*str >= '0' && *str <= '9')))
		return (1); // sprawdza czy jakis znak jest inny od '-' '+' lub cyfry
	if ((*str == '+' || *str == '-') && !(str[1] >= '0' && str[1] <= '9'))
		return (1); // sprawdza czy po '+' lub '-' jest cyfra
	str++;
	while (*str) // petla dziala dopoki wartosc na ktora wskazuje str po inkrementacji nie jest 0
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

// sprawdza czy dana liczba pojawila sie juz w stosie

int error_repetition(t_stack *a, int nbr)
{
	if (a == NULL)
		return (0);
	while (a)
	{
		if (a->value == nbr)
			return (1);
		a = a->next;
	}
	return (0);
}
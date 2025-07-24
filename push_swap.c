/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:46:55 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/24 15:05:13 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// create the stack // FULLY DONE
int	main(int argc, char **argv)
{
	t_struct	env;

	init_var(&env);
	if (!env.cost)
		return (1);
	env.cost->cost_a = INT_MAX;
	env.cost->cost_b = INT_MAX;
	(void)env.head_b;
	if (argc < 2)
		return (1);
	if (fill_double_chain(&env, argv))
		return (write(1, "Error\n", 6));
	if (check_same_nbr(&env))
		return (write(1, "Error\n", 6));
	calculate_tail(&env);
	if (argc == 3)
		sort_two(&env);
	if (argc == 4)
		sort_tree(&env);
	if (argc > 4)
	{
		fill_stack_b(&env);
		env.tmp_b = env.head_b;
		while (env.tmp_b)
		{
			calculate_cost(&env);
			push_back(&env);
			env.tmp_b = env.head_b;
		}
	}
	update_index_a(&env);
	update_index_b(&env);
	calculate_tail(&env);
	env.tmp = env.head_a;
	while (env.tmp)
	{
		printf("le noeud numero stack_a %i contient la valeur %i\n",
			env.tmp->index, env.tmp->value);
		env.tmp = env.tmp->next;
	}
	printf("\n");
	env.tmp_b = env.head_b;
	while (env.tmp_b)
	{
		printf("le noeud numero stack_b %i contient la valeur %i\n",
			env.tmp_b->index, env.tmp_b->value);
		env.tmp_b = env.tmp_b->next;
	}
	return (0);
}

int	check_same_nbr(t_struct *env)
{
	env->tmp = env->head_a;
	while (env->tmp != NULL)
	{
		env->tmp_check_double = env->tmp->next;
		while (env->tmp_check_double != NULL)
		{
			if (env->tmp_check_double->value == env->tmp->value)
			{
				ft_free_lst(env);
				return (1);
			}
			env->tmp_check_double = env->tmp_check_double->next;
		}
		env->tmp = env->tmp->next;
	}
	return (0);
}

void	free_splited_nbr(t_struct *env)
{
	int	i;

	i = 0;
	if (!env->splited_nbr)
		return ;
	while (env->splited_nbr[i])
	{
		free(env->splited_nbr[i]);
		i++;
	}
	free(env->splited_nbr);
}
void	ft_free_lst(t_struct *env)
{
	t_stack	*tmp;
	t_stack	*next;

	if (env->head_a == NULL)
		return ;
	tmp = env->head_a;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	env->head_a = NULL;
}
int	calculate_tail(t_struct *env)
{
	env->tmp = env->head_a;
	env->tmp_b = env->head_b;
	if (env->tmp)
	{
		while (env->tmp)
		{
			env->tail_a = env->tmp;
			env->tmp = env->tmp->next;
		}
	}
	if (env->tmp_b)
	{
		while (env->tmp_b)
		{
			env->tail_b = env->tmp_b;
			env->tmp_b = env->tmp_b->next;
		}
	}
	return (0);
}

int	update_index_b(t_struct *env)
{
	int	index;

	env->tmp_b = env->head_b;
	if (env->tmp_b)
	{
		index = 0;
		while (env->tmp_b)
		{
			env->tmp_b->index = index;
			env->tmp_b = env->tmp_b->next;
			index++;
		}
	}
	return (index);
}
int	update_index_a(t_struct *env)
{
	int	index;

	env->tmp = env->head_a;
	if (env->tmp)
	{
		index = 0;
		while (env->tmp)
		{
			env->tmp->index = index;
			env->tmp = env->tmp->next;
			index++;
		}
	}
	return (index);
}

// create/use algo
// push toutes les valeurs de stack a dans stack b a l exeption de la plus grande valeur de stack a la derniere de la stack sauf si c est la plus grande alors ca seras l avant derniere
// en fonction de mon max restant dans a et de mon autre valeur regarder le top et le bottom de stack b et si la valeur est comprise entre autre valeur et max je
// repete l etape 2 tant que b n est pas vide
// faire un algo different pour 3 et 5

// run test

/*
1 2 3
1 3 2
2 1 3
2 3 1
3 2 1
3 1 2
*/
// ra + rb = rr => max(dista, distb)

// min(min(max(stack.size.a - dist.a , dist.b), max(dist.a , stack.size.b
// - dist.b)), dist.a + dist.b)

// min(1 min(2 3))

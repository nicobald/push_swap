/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:46:55 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/31 00:09:36 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_var(t_struct *env)
{
	env->index_argv = 1;
	env->head_a = NULL;
	env->head_b = NULL;
	env->node = NULL;
	env->pos = 0;
	env->a = 'a';
	env->b = 'b';
	env->c = 'c';
	env->cost = malloc(sizeof(t_move_info));
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
				free(env->cost);
				return (1);
			}
			env->tmp_check_double = env->tmp_check_double->next;
		}
		env->tmp = env->tmp->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	env;

	init_var(&env);
	if (!env.cost)
		return (1);
	if (argc < 2)
	{
		free(env.cost);
		return (1);
	}
	if (fill_double_chain(&env, argv))
	{
		free(env.cost);
		ft_free_lst(&env);
		free_splited_nbr(&env);
		return (write(1, "Error\n", 6));
	}
	if (check_same_nbr(&env))
		return (write(1, "Error\n", 6));
	calculate_tail(&env);
	algorithm(&env);
	ft_free_lst(&env);
	free(env.cost);
	return (0);
}

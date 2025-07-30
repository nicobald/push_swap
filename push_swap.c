/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:46:55 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/30 17:32:15 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	update_index_a(&env);
	ft_free_lst(&env);
	free(env.cost);
	return (0);
}




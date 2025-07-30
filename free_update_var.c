/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_update_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:10:33 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/30 17:11:06 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	int index;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:06:12 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/30 21:54:15 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int double_swap(t_stack **head_a, t_stack **head_b, char stack_id)
{
	swap(head_a, stack_id);
	swap(head_b, stack_id);
	write(1, "ss\n", 3);
	return(0);
}
int double_rotate(t_struct *env, char stack_id)
{
	rotate(&env->head_a, &env->tail_a, stack_id);
	rotate(&env->head_b, &env->tail_b, stack_id);
	write(1, "rr\n", 3);
	return(0);
}
int double_reverse_rotate(t_struct *env, char stack_id)
{
	reverse_rotate(&env->head_a, &env->tail_a, stack_id);
	reverse_rotate(&env->head_b, &env->tail_b, stack_id);
	write(1, "rrr\n", 4);
	return(0);
}

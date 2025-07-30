/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:20:07 by nbaldes           #+#    #+#             */
/*   Updated: 2025/07/30 17:31:44 by nbaldes          ###   ########.fr       */
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

t_stack	*ft_new_node(int value, int index)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = index;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_lstadd_back_double_chained(t_stack **lst, t_stack *new)
{
	t_stack	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

int	fill_double_chain(t_struct *env, char **argv)
{
	while (argv[env->index_argv])
	{
		env->index_node_lst = -1;
		env->splited_nbr = ft_split(argv[env->index_argv], ' ');
		if (!env->splited_nbr)
			return (1);
		while (env->splited_nbr[++env->index_node_lst])
		{
			if (ft_atol(env->splited_nbr[env->index_node_lst]) > INT_MAX
				|| ft_atol(env->splited_nbr[env->index_node_lst]) < INT_MIN)
				return (1);
			if (check_nbr(env->splited_nbr))
				return (1);
			env->node = ft_new_node(ft_atoi(env->splited_nbr[env->index_node_lst]),
					env->pos);
			ft_lstadd_back_double_chained(&env->head_a, env->node);
			env->pos++;
		}
		free_splited_nbr(env);
		env->index_argv++;
	}
	return (0);
}

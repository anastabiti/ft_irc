/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:48:54 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/11 09:22:21 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parser.hpp"

int	main(int ac, char **av)
{
	if (checker(ac, av) == 0)
		return (0);
	parse_command();
	//enter here : start exec
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:36:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/29 09:55:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int		main(int ac, const char **av)
{
	std::fstream	ifs;
	std::streambuf	*cinbuf;
	std::string		line("");

	cinbuf = std::cin.rdbuf();
	if (ac > 1)
	{
		ifs.open(av[1], std::ios::binary | std::ios::in);
		if (ifs.good() == false)
		{
			std::cerr << "Error opening " << av[1] << std::endl;
			return 1;
		}
		std::cin.rdbuf(ifs.rdbuf());
	}
	while (std::getline(std::cin, line))
	{
		std::cout << "line : " << line << std::endl;
	}
	std::cin.rdbuf(cinbuf);
	std::cout << "BYE" << std::endl;
	return (0);
}

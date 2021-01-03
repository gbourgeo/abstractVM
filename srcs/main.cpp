/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:36:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/03 21:03:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "LexerParser.hpp"
#include "Token.hpp"
#include "OperandFactory.hpp"

int		main(int ac, const char **av)
{
	try
	{
		LexerParser		lp(av[1]);
		Token			token;

		lp.tokenise(token);
		lp.parse(token);
	}
	catch (LexerParser::OpenFileException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (LexerParser::LexerParserException & e)
	{
		std::cerr << e.what() << std::endl;
	}

	OperandFactory	o;
	const IOperand *i = o.createOperand(Float, "10");
	std::cout << i->toString() << std::endl;
	delete i;

	(void)ac;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:36:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/24 12:31:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Token.hpp"
#include "OperandFactory.hpp"

int		main(int ac, const char **av)
{
	(void)ac;
	try
	{
		Instructions	instructions;
		Lexer			lexer(av[1], instructions);
		Parser			parser(instructions);
		Token			token;

		lexer.tokenise(token);
		parser.parse(token);
	}
	catch (Lexer::LexerException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (Parser::ParserException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/17 21:31:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser()
{}

Parser::~Parser()
{}

Parser::Parser(Parser const & src)
{
	*this = src;
}

Parser & Parser::operator=(Parser const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

void			Parser::parse( Token & tokens )
{
	std::cout << "Type	Instruction	Value" << std::endl;
	for (Token::t_token const *t = tokens.getNextToken(); t; t = tokens.getNextToken())
	{
		std::cout << t->type << "	";// << this->_instructions[t->type].name;
		if (t->ope != nullptr)
			std::cout << "		" << t->ope->toString();
		std::cout << std::endl;
	}
}

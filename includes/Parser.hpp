/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/24 13:11:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <list>
# include <stdexcept>
# include "Token.hpp"
# include "OperandFactory.hpp"

class Parser
{
public:
	Parser();
	Parser(Instructions const & inst);
	~Parser();
	Parser(Parser const & src);
	Parser & operator=(Parser const & rhs);

	void		parse( Token & tokens );

	class	ParserException : public std::exception
	{
	public:
		ParserException(std::size_t lineNb, const char * error);

		virtual const char * what() const throw()
		{
			return this->_error.c_str();
		}
	private:
		std::string		_error;
	};

private:
	Instructions const			*_instructions;
	OperandFactory				_op;
	std::list<IOperand const *>	_stack;
	bool						_loop;

	/* Tokens instructions functions */
	void			push(Token::t_token const * token);
	void			pop(Token::t_token const * token);
	void			dump(Token::t_token const * token);
	void			assert(Token::t_token const * token);
	void			add(Token::t_token const * token);
	void			sub(Token::t_token const * token);
	void			mul(Token::t_token const * token);
	void			div(Token::t_token const * token);
	void			mod(Token::t_token const * token);
	void			print(Token::t_token const * token);
	void			exit(Token::t_token const * token);
};


#endif // PARSER_HPP
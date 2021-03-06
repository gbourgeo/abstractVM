/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/31 10:52:18 by gbourgeo         ###   ########.fr       */
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
	void			_push(Token::t_token const * token);
	void			_pop(Token::t_token const * token);
	void			_dump(Token::t_token const * token);
	void			_assert(Token::t_token const * token);
	void			_add(Token::t_token const * token);
	void			_sub(Token::t_token const * token);
	void			_mul(Token::t_token const * token);
	void			_div(Token::t_token const * token);
	void			_mod(Token::t_token const * token);
	void			_print(Token::t_token const * token);
	void			_exit(Token::t_token const * token);
};


#endif // PARSER_HPP
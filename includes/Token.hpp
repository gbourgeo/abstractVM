/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/17 21:31:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <vector>
# include <algorithm>
# include "OperandFactory.hpp"

class Token
{
public:
	Token();
	~Token();
	Token(Token const & src);
	Token & operator=(Token const & rhs);
	/* Token type enumeration */
	enum eTokenType
	{
		Push,
		Pop,
		Dump,
		Assert,
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Print,
		Exit,
	};
	/* Tokens structure */
	typedef struct	s_token
	{
		eTokenType		type;
		IOperand const	*ope;
	}				t_token;

	void			addToken(eTokenType tokenType, std::string const & operandValue, eOperandType opType);
	void			addToken(eTokenType tokenType);
	t_token const	*getNextToken( void );

private:
	/* Tokens list */
	std::vector<t_token>	_tokens;
	OperandFactory			_op;
};

#endif // TOKEN_HPP

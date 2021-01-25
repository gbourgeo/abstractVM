/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/24 13:15:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <vector>
# include <algorithm>
# include "Instructions.hpp"

class Token
{
public:
	Token();
	~Token();
	Token(Token const & src);
	Token & operator=(Token const & rhs);

	/* Tokens structure */
	typedef struct	s_token
	{
		std::size_t						lineNb;
		Instructions::eInstructionType	instruction;
		IOperand::eOperandType			operand;
		std::string						operandValue;
	}				t_token;

	void			addToken(t_token token);
	t_token const	* getNextToken( void );
	t_token const	* getLastToken( void ) const;

	void reset(void); // A supprimer !
private:
	/* Tokens list */
	std::vector<t_token>	_tokens;
	std::size_t				_idx;
};

#endif // TOKEN_HPP

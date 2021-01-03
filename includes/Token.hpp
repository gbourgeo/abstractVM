/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/03 21:00:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <vector>

class Token
{
	public:
		Token();
		~Token();
		Token(Token const & src);
		Token & operator=(Token const & rhs);

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
			Comment,
			End,
		};
		void addToken(eTokenType type, std::string & word);
		void addToken(eTokenType type, std::string & word, std::string & args);

	private:
		/* Tokens structure */
		struct s_token
		{
			eTokenType		_type;
			std::string		_word;
			std::string		_args;
		};
		/* Tokens list */
		std::vector<struct s_token>		_tokens;
};

#endif // TOKEN_HPP

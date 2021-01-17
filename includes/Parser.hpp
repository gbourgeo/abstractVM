/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/17 12:03:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include "Token.hpp"

class Parser
{
public:
	Parser();
	~Parser();
	Parser(Parser const & src);
	Parser & operator=(Parser const & rhs);

	void		parse( Token & tokens );

private:
};

#endif // PARSER_HPP
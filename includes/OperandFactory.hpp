/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:13:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/23 22:52:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "Operand.hpp"

class OperandFactory
{
public:
	OperandFactory();
	~OperandFactory();
	OperandFactory(OperandFactory const & src);
	OperandFactory & operator=(OperandFactory const & rhs);

	IOperand const * createOperand( IOperand::eOperandType type, std::string const & value) const;

private:
	IOperand const * createInt8( std::string const & value) const;
	IOperand const * createInt16( std::string const & value) const;
	IOperand const * createInt32( std::string const & value) const;
	IOperand const * createFloat( std::string const & value) const;
	IOperand const * createDouble( std::string const & value) const;
};

#endif // OPERANDFACTORY_HPP

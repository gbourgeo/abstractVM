/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:42:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/26 21:33:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

class IOperand {
public:

	enum eOperandType {
		Int8,
		Int16,
		Int32,
		Float,
		Double,
		None,
	};

	enum ePrecision {
		Int8_p,
		Int16_p,
		Int32_p,
		Float_p,
		Double_p,
		None_p,
	};

	virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
	virtual eOperandType getType( void ) const = 0; // Type of the instance

	virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo

	virtual std::string const & toString( void ) const = 0; // String representation of the instance

	virtual ~IOperand( void ) {}
};

#endif // IOPERAND_HPP

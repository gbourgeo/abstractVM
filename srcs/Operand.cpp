/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:41:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/31 14:04:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include "Instructions.hpp"

template<class T>
Operand<T>::Operand(): _value(0), _type(IOperand::Int8), _precision(IOperand::Int8_p)
{}

template<class T>
Operand<T>::Operand(std::string const & value, IOperand::eOperandType type):
	_s_value(value), _type(type), _precision(static_cast<ePrecision>(type))
{
	if (type == IOperand::Int8 || type == IOperand::Int16 || type == IOperand::Int32)
		this->_value = std::stoi(value);
	if (type == IOperand::Float)
		this->_value = std::stof(value);
	if (type == IOperand::Double)
		this->_value = std::stod(value);
}

template<class T>
Operand<T>::Operand(T const & value, IOperand::eOperandType type):
	_value(value), _s_value(std::to_string(value)), _type(type), _precision(static_cast<ePrecision>(type))
{}

template<class T>
Operand<T>::~Operand()
{}

template<class T>
Operand<T>::Operand(Operand const & src)
{
	*this = src;
}

template<class T>
Operand<T> & Operand<T>::operator=(Operand<T> const & rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs._value;
		this->_s_value = rhs._s_value;
		this->_type = rhs._type;
		this->_precision = rhs._precision;
	}
	return *this;
}

template<class T>
int					Operand<T>::getPrecision( void ) const
{
	return this->_precision;
}

template<class T>
IOperand::eOperandType	Operand<T>::getType( void ) const
{
	return this->_type;
}

template<class T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs ) const
{
	T		res;
	T		sum;

	if (this->getPrecision() < rhs.getPrecision())
		return rhs + *this;
	res = static_cast<T>(std::stod(rhs.toString()));
	sum = this->_value + res;
	if (this->_value > 0 && res > 0)
	{
		if (sum < res)
			throw Operand<int8_t>::OperandException("Addition overflows.");
	}
	else if (this->_value < 0 && res < 0)
	{
		if (sum > res)
			throw Operand<int8_t>::OperandException("Addition underflows.");
	}
	return new Operand<T>(sum, this->getType());
}

template<class T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
	T		res;
	T		sub;

	if (this->getPrecision() < rhs.getPrecision())
	{
		return rhs - *this;
	}
	res = static_cast<T>(std::stod(rhs.toString()));
	sub = this->_value - res;
	if (this->_value > 0 && res < 0)
	{
		if (sub < this->_value)
			throw Operand<int8_t>::OperandException("Substraction overflows.");
	}
	else if (this->_value < 0 && res > 0)
	{
		if (sub > this->_value)
			throw Operand<int8_t>::OperandException("Substraction underflows.");
	}
	return new Operand<T>(sub, this->getType());
}

template<class T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
	T		res;
	T		mul;

	if (this->getPrecision() < rhs.getPrecision())
		return rhs * *this;
	res = static_cast<T>(std::stod(rhs.toString()));
	mul = this->_value * res;
	if (this->_value > 0 && res > 0)
	{
		if (mul < res)
			throw Operand<int8_t>::OperandException("Multiplication overflows.");
	}
	else if (this->_value < 0 && res < 0)
	{
		if (mul > res)
			throw Operand<int8_t>::OperandException("Multiplication underflows.");
	}
	return new Operand<T>(mul, this->getType());
}

template<class T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
	T		res;
	T		div;

	if (this->getPrecision() < rhs.getPrecision())
		return rhs / *this;
	res = static_cast<T>(std::stod(rhs.toString()));
	if (res > -0.0000001 && res < 0.0000001)
		throw Operand<int8_t>::OperandException("Division by 0.");
	div = this->_value / res;
	return new Operand<T>(div, this->getType());
}

template<class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
	T		res;
	T		mod;

	if (this->getPrecision() < rhs.getPrecision())
		return rhs % *this;
	res = static_cast<T>(std::stod(rhs.toString()));
	if (res > -0.0000001 && res < 0.0000001)
		throw Operand<int8_t>::OperandException("Division by 0.");
	mod = std::fmod(this->_value, res);
	return new Operand<T>(mod, this->getType());
}

template<class T>
std::string const & Operand<T>::toString( void ) const
{
	return this->_s_value;
}

template<class T>
Operand<T>::OperandException::OperandException(const char * error)
{
	this->_error = error;
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/24 14:11:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer():
	_file(nullptr), _cinbuf(std::cin.rdbuf()), _lineNb(0), _instructions(nullptr)
{
	throw Lexer::LexerException(this->_lineNb, this->_instructions);
}

Lexer::Lexer(char const * file, Instructions const & instructions):
	_file(file), _cinbuf(std::cin.rdbuf()), _lineNb(0), _instructions(&instructions)
{
	if (this->_file)
	{
		this->_ifs.open(this->_file, std::ios::binary | std::ios::in);
		if (this->_ifs.good() == false)
		{
			throw Lexer::LexerException(this->_lineNb, this->_file);
		}
		/* Assignation d'un nouveau buffer à std::cin */
		std::cin.rdbuf(this->_ifs.rdbuf());
	}
}

Lexer::~Lexer()
{
	/* Fermeture du fichier si présent */
	if (this->_file != nullptr)
	{
		this->_ifs.close();
	}
	/* Restauration de l'ancien buffer de std::cin */
	std::cin.rdbuf(this->_cinbuf);
}

Lexer::Lexer(Lexer const & src)
{
	*this = src;
}

Lexer & Lexer::operator=(Lexer const & rhs)
{
	if (this != &rhs)
	{
		this->_file = rhs._file;
		this->_cinbuf = rhs._cinbuf;
		this->_lineNb = rhs._lineNb;
	}
	return *this;
}

void	Lexer::tokenise( Token & token )
{
	std::string		line("");

	/* Lecture des commandes */
	while (std::getline(std::cin, line))
	{
		std::istringstream					ss(line);
		std::istream_iterator<std::string>	beg(ss), end;
		std::vector<std::string>			tokens(beg, end);
		Token::t_token						result;

		this->_lineNb++;
		for (std::size_t i = 0; i < tokens.size(); i++)
		{
			if (tokens.at(i)[0] == ';' && tokens.at(i)[1] != ';')
			{
				tokens.erase(tokens.begin() + i, tokens.end());
				break ;
			}
		}
		if (tokens.size() == 0)
			continue ;
		if (tokens.at(0)[1] == ';')
		// if (tokens.at(0).compare(";;") == 0)
		{
			token.addToken((Token::t_token){ this->_lineNb, Instructions::Exit, IOperand::None, tokens.at(0) });
			break ;
		}
		try
		{
			result.lineNb = this->_lineNb;
			result.instruction = this->_instructions->getInstruction(tokens.at(0));
			std::size_t nbArgs = this->_instructions->getInstructionNbArgs(tokens.at(0));
			if (tokens.size() < nbArgs + 1)
				throw Lexer::LexerException(this->_lineNb, "Invalid instruction: Missing value", tokens.at(0));
			if (tokens.size() > nbArgs + 1)
				throw Lexer::LexerException(this->_lineNb, "Invalid instruction: Too many values", tokens.at(0));
			if (nbArgs > 0)
			{
				result.operand = this->_instructions->getOperand(tokens.at(1));
				result.operandValue = this->_instructions->getOperandValue(tokens.at(1));
			}
			token.addToken(result);
		}
		catch (Instructions::InstructionsException & e)
		{
			throw Lexer::LexerException(this->_lineNb, e);
		}
	}
}

Lexer::LexerException::LexerException(std::size_t lineNb, const char *file)
{
	if (file != nullptr)
		this->_error = "Line " + std::to_string(lineNb) + " : " + "Unable to open file : '" + std::string(file) + "'";
	else
		this->_error = "Line " + std::to_string(lineNb) + " : " + "Unable to read from std::cin";
}

Lexer::LexerException::LexerException(std::size_t lineNb, Instructions const * instrutions)
{
	if (instrutions != nullptr)
		this->_error = "Line " + std::to_string(lineNb) + " : " + "Unknown error";
	else
		this->_error = "Line " + std::to_string(lineNb) + " : " + "No instructions given";
}

Lexer::LexerException::LexerException(std::size_t lineNb, Instructions::InstructionsException & e)
{
	this->_error = "Line " + std::to_string(lineNb) + " : " + std::string(e.what());
}

Lexer::LexerException::LexerException(std::size_t lineNb, const char *error, std::string const & value)
{
	this->_error = "Line " + std::to_string(lineNb) + " : " + value + " : " + std::string(error);
}

Lexer::LexerException::LexerException(std::size_t lineNb, const char *error, Token::t_token const * token)
{
	(void)token;
	this->_error = "Line " + std::to_string(lineNb) + " : " + std::string(error);
}

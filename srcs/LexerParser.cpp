/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/10 02:41:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LexerParser.hpp"

LexerParser::t_inst		LexerParser::_instructions[] = {
	{ "push",   Token::Push,   1 },
	{ "pop",    Token::Pop,    0 },
	{ "dump",   Token::Dump,   0 },
	{ "assert", Token::Assert, 1 },
	{ "add",    Token::Add,    0 },
	{ "sub",    Token::Sub,    0 },
	{ "mul",    Token::Mul,    0 },
	{ "div",    Token::Div,    0 },
	{ "mod",    Token::Mod,    0 },
	{ "print",  Token::Print,  0 },
	{ "exit",   Token::Exit,   0 },
};

LexerParser::t_operands	LexerParser::_values[] = {
	{ "int8",   Int8  , &LexerParser::intOperandCheck },
	{ "int16",  Int16 , &LexerParser::intOperandCheck },
	{ "int32",  Int32 , &LexerParser::intOperandCheck },
	{ "float",  Float , &LexerParser::floatOperandCheck },
	{ "double", Double, &LexerParser::doubleOperandCheck },
};

LexerParser::LexerParser():
	_file(nullptr), _cinbuf(std::cin.rdbuf()), _lineNb(1)
{}

LexerParser::LexerParser(char const * file):
	_file(file), _cinbuf(std::cin.rdbuf()), _lineNb(1)
{
	if (this->_file)
	{
		this->_ifs.open(this->_file, std::ios::binary | std::ios::in);
		if (this->_ifs.good() == false)
		{
			throw LexerParser::OpenFileException(this->_file);
		}
		/* Assignation d'un nouveau buffer à std::cin */
		std::cin.rdbuf(this->_ifs.rdbuf());
	}
}

LexerParser::~LexerParser()
{
	/* Fermeture du fichier si présent */
	if (this->_file != nullptr)
	{
		this->_ifs.close();
	}
	/* Restauration de l'ancien buffer de std::cin */
	std::cin.rdbuf(this->_cinbuf);
}

LexerParser::LexerParser(LexerParser const & src)
{
	*this = src;
}

LexerParser & LexerParser::operator=(LexerParser const & rhs)
{
	if (this != &rhs)
	{
		this->_file = rhs._file;
		this->_cinbuf = rhs._cinbuf;
	}
	return *this;
}

void	LexerParser::tokenise( Token & token )
{
	std::size_t				inst_size;
	std::string				line("");
	LexerParser::t_result	opVal;

	inst_size = sizeof(this->_instructions) / sizeof(this->_instructions[0]);
	/* Lecture des commandes */
	while (std::getline(std::cin, line))
	{
		std::istringstream	ss(line);
		std::istream_iterator<std::string> beg(ss), end;
		std::vector<std::string> tokens(beg, end);
		std::size_t		i;

		for (i = 0; i < tokens.size(); i++)
		{
			if (tokens.at(i)[0] == ';' && tokens.at(i)[1] != ';')
			{
				tokens.erase(tokens.begin() + i, tokens.end());
				break ;
			}
		}
		if (tokens.size() != 0)
		{
			if (tokens.at(0)[1] == ';')
			// if (tokens.at(0).compare(";;") == 0)
				break ;
			for (i = 0; i < inst_size; i++)
			{
				if (tokens.at(0).compare(this->_instructions[i].name) == 0)
				{
					if (tokens.size() != this->_instructions[i].nbArgs + 1)
						throw LexerParser::LexerParserException(this->_lineNb, "Wrong number of argument for instruction", tokens.at(0));
					if (this->_instructions[i].nbArgs != 0)
						opVal = LexerParser::checkOperand(tokens.at(1));
					token.addToken(this->_instructions[i].type, opVal.value, opVal.type);
					break ;
				}
			}
			if (i >= inst_size)
				throw LexerParserException(this->_lineNb, "Unknown instruction", tokens.at(0));
		}
		this->_lineNb++;
	}
}

LexerParser::t_result		LexerParser::checkOperand(std::string const & operand) const
{
	std::size_t	parent_left = operand.find('(');
	std::size_t	parent_right = operand.find(')');
	std::string	value;
	std::size_t	value_size = sizeof(this->_values) / sizeof(this->_values[0]);
	std::size_t	i;

	if (parent_left == std::string::npos || parent_right == std::string::npos)
		throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand format: Missing '(' or ')'", operand);
	value = operand.substr(parent_left + 1, parent_right - parent_left);
	for (i = 0; i < value_size; i++)
	{
		if (operand.compare(0, parent_left, this->_values[i].name) == 0)
			(this->*this->_values[i].checkValue)(value);
		return (t_result){ this->_values[i].type, value };
	}
	throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand format: Unrecognized operand", operand);
}

void			LexerParser::intOperandCheck(std::string const & value) const
{
	std::size_t		i;

	if (value.length() == 0)
		throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value: Empty value", value);
	for (i = 0; i < value.length(); i++)
	{
		if ((value.at(i) == '-' && i != 0)
		|| !(value.at(i) >= '0' && value.at(i) <= '9'))
			throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value", value);
	}
}

void			LexerParser::floatOperandCheck(std::string const & value) const
{
	std::size_t	i;
	int			found_point;

	found_point = 0;
	if (value.length() == 0)
		throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value: Empty value", value);
	for (i = 0; i < value.length(); i++)
	{
		if ((value.at(i) == '-' && i != 0)
			|| !(value.at(i) >= '0' && value.at(i) <= '9'))
		{
			found_point = (value.at(i) == '.');
			if (found_point == 0)
				throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value", value);
		}
	}
	if (found_point == 0)
			throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value: Missing point", value);
}

void			LexerParser::doubleOperandCheck(std::string const & value) const
{
	std::size_t	i;
	char		found_point;

	found_point = 0;
	if (value.length() == 0)
		throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value: Empty value", value);
	for (i = 0; i < value.length(); i++)
	{
		if ((value.at(i) == '-' && i != 0)
			|| !(value.at(i) >= '0' && value.at(i) <= '9'))
		{
			found_point = (value.at(i) == '.');
			if (found_point == 0)
				throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value", value);
		}
	}
	if (found_point == 0)
			throw LexerParser::LexerParserException(this->_lineNb, "Invalid operand value: Missing point", value);
}

void			LexerParser::parse( Token & token)
{
	std::cout << "Type		Instruction	Value" << std::endl;
	for (Token::t_token const *t = token.getNextToken(); t; t = token.getNextToken())
	{
		std::cout << t->_type << std::endl;
	}
}

LexerParser::OpenFileException::OpenFileException(const char *file)
{
	if (file != nullptr)
		this->_error = "Unable to open file : '" + std::string(file) + "'";
	else
		this->_error = "Unable to read from std::cin";
}

LexerParser::LexerParserException::LexerParserException(std::size_t lineNb, const char *error, std::string const & instruction)
{
	this->_error = "Line " + std::to_string(lineNb) + ": " + std::string(error) + ": '" + instruction + "'";
}

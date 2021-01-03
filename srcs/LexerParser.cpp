/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/03 21:11:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LexerParser.hpp"

LexerParser::LexerParser():
	_file(nullptr), _cinbuf(std::cin.rdbuf())
{}

LexerParser::LexerParser(char const * file):
	_file(file), _cinbuf(std::cin.rdbuf())
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
	const t_token	instruction[] = {
		{ 2, "push",   Token::Push },
		{ 1, "pop",    Token::Pop },
		{ 1, "dump",   Token::Dump },
		{ 2, "assert", Token::Assert },
		{ 1, "add",    Token::Add },
		{ 1, "sub",    Token::Sub },
		{ 1, "mul",    Token::Mul },
		{ 1, "div",    Token::Div },
		{ 1, "mod",    Token::Mod },
		{ 1, "print",  Token::Print },
		{ 1, "exit",   Token::Exit },
	};
	std::string		line("");
	std::size_t		lineNb;

	/* Lecture des commandes */
	lineNb = 1;
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
			for (i = 0; i < sizeof(instruction) / sizeof(instruction[0]); i++)
			{
				if (tokens.at(0).compare(instruction[i].value) == 0)
				{
					if (tokens.size() != instruction[i].nbArgs)
						throw LexerParser::LexerParserException(lineNb, "Wrong number of argument for instruction", tokens.at(0));
					if (instruction[i].nbArgs == 1)
						token.addToken(instruction[i].type, tokens.at(0));
					else if (instruction[i].nbArgs == 2)
						token.addToken(instruction[i].type, tokens.at(0), tokens.at(1));
					break ;
				}
			}
			if (i >= sizeof(instruction) / sizeof(instruction[0]))
				throw LexerParserException(lineNb, "Unknown instruction", tokens.at(0));
		}
		lineNb++;
	}
}

void	LexerParser::parse( Token & token)
{
	(void)token;
}

LexerParser::OpenFileException::OpenFileException(const char *file)
{
	if (file != nullptr)
		this->_error = "Unable to open file : '" + std::string(file) + "'";
	else
		this->_error = "Unable to read from std::cin";
}

LexerParser::LexerParserException::LexerParserException(std::size_t lineNb, const char *error, std::string & instruction)
{
	this->_error = "Line " + std::to_string(lineNb) + ": " + std::string(error) + ": '" + instruction + "'";
}

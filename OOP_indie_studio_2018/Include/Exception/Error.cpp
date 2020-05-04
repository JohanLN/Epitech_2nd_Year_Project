/*
** EPITECH PROJECT, 2019
** OOP_nanotekspice_2018
** File description:
** TODO: add description
*/

#include "Error.hpp"

Error::Error(errNum num, std::string msg, errLevel level) throw()
{
    this->_errNum = num;
    this->_msg = msg;
    this->_errLevel = level;
}

Error::~Error() throw() {}

errNum Error::getErrNum() const
{
    return (this->_errNum);
}

errLevel Error::getErrLevel() const
{
    return (this->_errLevel);
}

const char *Error::what() const throw()
{
    return (this->_msg.c_str());
}

std::string Error::getMsg() const
{
    return (this->_msg);
}
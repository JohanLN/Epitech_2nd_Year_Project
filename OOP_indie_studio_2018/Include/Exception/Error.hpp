/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** TODO: add description
*/

#include <string>
#include <exception>

#ifndef OOP_NANOTEKSPICE_2018_ERROR_HPP
#define OOP_NANOTEKSPICE_2018_ERROR_HPP

# define EXIT_FAIL 84
# define EXIT_SUCC 0

enum errNum {
    NONE = 0,
    DEFAULT = 84
};

enum errLevel {
    INFO = 0,
    MINOR,
    MAJOR
};

class Error: public std::exception {
    public:
        Error(errNum errNum, std::string msg, errLevel errLevel) throw();
        ~Error() throw();

        virtual const char *what() const throw();
        errNum getErrNum() const;
        errLevel getErrLevel() const;
        std::string getMsg() const;
    private:
        errNum _errNum;
        std::string _msg;
        errLevel _errLevel;
    };

#endif //OOP_ARCADE_2018_ERROR_HPP
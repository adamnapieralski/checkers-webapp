/**
 * @file CheckersPy.cc
 * @brief Implementation of python module for C++ using Boost.Python
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include <boost/python.hpp>
#include "Checkers.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(checkers)
{
    class_<Checkers, boost::noncopyable>("Checkers", no_init)
        .def("getInstance", &Checkers::getInstance, return_value_policy<reference_existing_object>())
            .staticmethod("getInstance")
        .def("initialize", &Checkers::initialize)
        .def("fenInitialize", &Checkers::fenInitialize)
        .def("getIsUserWhite", &Checkers::getIsUserWhite)
        .def("getUserName", &Checkers::getUserName)
        .def("processUserMove", &Checkers::processUserMove)
        .def("makeComputerMove", &Checkers::makeComputerMove)
        .def("getGameState", &Checkers::getGameState)
    ;

    class_<GameState>("GameState")
        .def_readonly("userName", &GameState::userName)
        .def_readonly("isUserWhite", &GameState::isUserWhite)
        .def_readonly("boardFEN", &GameState::boardFEN)
        .def_readonly("isUserTurn", &GameState::isUserTurn)
        .def_readonly("isInMultipleMove", &GameState::isInMultipleMove)
        .def_readonly("uAP", &GameState::uAP)
        .def_readonly("uAK", &GameState::uAK)
        .def_readonly("cAP", &GameState::cAP)
        .def_readonly("cAK", &GameState::cAK)
        .def_readonly("hasGameEnded", &GameState::hasGameEnded)
        .def_readonly("score", &GameState::score)
    ;

    enum_<Score>("Score")
        .value("IN_PROGRESS", IN_PROGRESS)
        .value("USER_WON", USER_WON)
        .value("USER_LOST", USER_LOST)
        .value("DRAW", DRAW)
    ;
}

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
        .def("getIsUserWhite", &Checkers::getIsUserWhite)
        .def("getUserName", &Checkers::getUserName)
        .def("processUserMove", &Checkers::processUserMove)
        .def("makeComputerMove", &Checkers::makeComputerMove)
        .def("getGameState", &Checkers::getGameState)
    ;

    class_<GameState>("GameState")
        .def_readonly("boardFEN", &GameState::boardFEN)
    ;

}

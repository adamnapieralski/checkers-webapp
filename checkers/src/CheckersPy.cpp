/**
 * Projekt Zaawansowane Programowanie w C++ - Warcaby
 * 24.04.2020
 * 
 * Autorzy: Patrycja Cieplicka, Adam Napieralski
 * 
 * 
 * */

#include <boost/python.hpp>
#include "Checkers.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(checkers)
{
    class_<Checkers>("Checkers")
        .def("initialize", &Checkers::initialize)
        .def("getIsUserWhite", &Checkers::getIsUserWhite)
        .def("getUserName", &Checkers::getUserName)
        .def("findTile", &Checkers::findTile)
    ;

    // def("findTile", Checkers::findTile);   
}

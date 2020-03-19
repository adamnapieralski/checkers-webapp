#include <boost/python.hpp>
#include "Checkers.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(checkers)
{
    boost::python::def("findTile", Checkers::findTile);   
}

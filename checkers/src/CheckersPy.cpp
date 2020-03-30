#include <boost/python.hpp>
#include "Checkers.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(checkers)
{
    boost::python::def("findTile", Checkers::findTile);   
}

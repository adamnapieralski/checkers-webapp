scons
scons --test
lcov --capture --directory checkers/ --output-file doc/coverage_info/coverage.info
genhtml doc/coverage_info/coverage.info --output-directory doc/coverage_info/

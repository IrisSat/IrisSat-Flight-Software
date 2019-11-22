-----------------------------------------------------------
  HOW TO USE
-----------------------------------------------------------
- Template and example files are given in the ./tests directory. Refer to the CppUTest manual for information on writing your first unit tests: https://cpputest.github.io/manual.html
- Place source files (i.e. *.c, *.cpp, and *.h) files into the "./src" or "./tests" directories. 
- Run "make" in this directory to build the test executable (./run_tests). Run "make clean" to clean.
- Ubuntu is needed to use the library files template project (e.g. use WSL with Ubuntu).

-----------------------------------------------------------
  HOW TO REBUILD THE LIB FILES (i.e. *.a)
-----------------------------------------------------------
To rebuild the libraries for a different system, go to the CppUTest website, and download the latest source code: https://cpputest.github.io/

Make sure you have the following libraries:
sudo apt-get update (use to update all libraries to their latest revision) 
sudo apt-get install make
sudo apt-get install gcc
sudo apt-get install g++
sudo apt-get install autoconf
sudo apt-get install libtools
sudo apt autoremove (delete any obsolete libraries)

Run the following commands in the uncompressed source code: 
cd cpputest_build
autoreconf .. -i
cd ../configure
make

The libraries can be found in ../lib.

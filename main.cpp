#include <iostream>
#include <fstream>
#include <sstream>
#include "Field.hpp"


using std::cout;
using std::ifstream;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return 1;
    }

    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);

    std::stringstream hack_stream1;
    std::stringstream hack_stream2;

    hack_stream1 << "3 3" << std::endl << "1 1 1" << std::endl << "1 2 1" << std::endl << "1 1 1" << std::endl;
    hack_stream2 << "3 3" << std::endl << "1 1 1" << std::endl << "1 3 1" << std::endl << "1 1 1" << std::endl;

    try {
        Field field;

        file.open(argv[1]);
        hack_stream1 >> field;
        hack_stream2 >> field;

        while (!field.is_done()) {
            field.tic();
        }

        field.result(cout);
    }
    catch (ifstream::failure& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
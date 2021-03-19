#include <string>
#include "Direction.hpp"
#include <iostream>

using namespace std;
namespace ariel {
    class Board{
        public :
			Board();
			void post(int row, int column, Direction d, std::string message);
			std::string read(int row, int column, Direction d, int length);
			void show();
    };
}
#include <iostream>

#include "Line.h"


using namespace std;

//#include <vector>


int main() {

	Line<int> lst = *(new Line<int>());

	lst.add(1);

	std::cout << lst.toString() << " " << lst[0];


}

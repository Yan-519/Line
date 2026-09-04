#include <iostream>

#include "Line.h"

using namespace std;

int main() {

	Line<int>* lst = new Line<int>();

	lst->add(1);

	for (size_t i = 0; i < 10; i++)
	{
		lst->add(i);
	}
	lst->to_set();

	for (int v : *lst) {
		std::cout << v << std::endl;
	}


}

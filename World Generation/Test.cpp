#include "Generation.h"
#include <iostream>
using namespace Generation;
int main(void)
{
	
	Generate test = Generate();

	//test.perlin_sprawl();

	std::cout << std::endl << std::endl << "Current Seed: " << seed << std::endl;
	test.terrain_picker_test();
	
	/*
	int *a = 0;
	int *b = 0;
	int c = 7;
	int d = 0;

	b = &c;
	a = &d;

	std::cout << *b << std::endl;

	*a = *b;

	*a = 2;

	std::cout << *b << std::endl;

	*b = *a;

	*a = 2;

	std::cout << *b << std::endl;

	*a = 4;

	std::cout << *b << std::endl;

	b = a;

	std::cout << *b << std::endl;

	*a = 10;

	std::cout << *b << std::endl;

	7
	7
	2
	2
	4
	10
	*/
	return 0;
}
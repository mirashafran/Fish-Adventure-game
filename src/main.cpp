#include "Controller.h"
#include <iostream>
#include "ResourceManager.h"

int main()
{
	Controller controller;
	try {
		controller.run();
		return EXIT_SUCCESS;
	}

	catch (const std::bad_cast& e) {
		std::cerr << "Error: bad cast - " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
		return EXIT_FAILURE;
	}
	

}

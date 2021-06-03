#include "Framework.hpp"
#include <string>
#include <thread>



int main(int argc, char* argv[]) {

	
	std::string startarg;

	if (argc > 1) {
		startarg = argv[1];
	}
	

	while (true) {
		{
			Framework framework;
			if (argc > 1) {
				framework.init(startarg);
			}
			else {
				framework.init();
			}


			while (framework.getrunning()) {

				framework.update();
				framework.eventhandle();
				framework.draw();

			}
		}
	}
		return 0;
}


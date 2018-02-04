#include <frbb/frbb.h>

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

auto f(bool _blow) -> int {
	if (_blow) {
		blow(nullptr);
	}
	else {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	frbb::soak();
	freeze {
		std::cout << "f() = " << f(false) << std::endl << std::flush;
		std::cout << "f() = " << f(true) << std::endl << std::flush;

		freeze {
			std::cout << "f() = " << f(false) << std::endl << std::flush;
			std::cout << "f() = " << f(true) << std::endl << std::flush;
		}
		burst(frbb::bubble, b1) {
			std::cout << "interrupted " << b1.bursted() << std::endl << std::flush;
		}
	}
	burst(frbb::bubble, b2) {
		std::cout << "interrupted " << b2.bursted() << std::endl << std::flush;
	}
	return 0;
}

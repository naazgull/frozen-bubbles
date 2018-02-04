#include <frbb/frbb.h>

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

bbb::bubble _b;
bbb::bubble _c;

auto f(bool _blow) -> int {
	if (_blow) {
		blow(_b);
	}
	else {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	freeze(_b) {
		std::cout << "f() = " << f(false) << std::endl << std::flush;
		std::cout << "f() = " << f(true) << std::endl << std::flush;

		freeze(_c) {
			std::cout << "f() = " << f(false) << std::endl << std::flush;
			std::cout << "f() = " << f(true) << std::endl << std::flush;-
		}
		intercept {
		}
	}
	intercept {
		std::cout << "interrupted" << std::endl << std::flush;
	}
	return 0;
}

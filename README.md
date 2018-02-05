INSTALLATION
------------
```
$ autoreconf -vfi && ./configure --prefix=/usr --sysconf=/etc "CXXFLAGS=-O3 -Wall"
$ make
$ sudo make install
```

USAGE
-----

## Compilation and linking

1. Include **<frbb/frbb.h>** header file
2. Ling against **-lfrozen-bubbles**

## How to use

Using exceptions as an example of correspondance:

| Exception                | Frozen bubbles           |
|:------------------------ |:------------------------ |
| try                      | freeze                   |
| catch(std::exception& e) | burst(frbb::bubble, b)   |
| throw std::exception()   | blow(new frbb::bubble()) |

EXAMPLE
--------

```
#include <frbb/frbb.h>

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

class MyBubble : public frbb::bubble {
public:
	MyBubble(std::string _reason) : __reason(_reason) {}
	MyBubble(MyBubble& _rhs) : frbb::bubble(_rhs) {
		this->__reason = _rhs.__reason;
	}
	MyBubble(MyBubble&& _rhs) : frbb::bubble(_rhs) {
		this->__reason = _rhs.__reason;
	}
	auto reason() -> std::string {
		return this->__reason;
	}
private:
	std::string __reason;
};

auto f(bool _blow) -> int {
	if (_blow) {
		blow(new MyBubble("this is a bubble"));
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
		std::cout << "f() = " << f(false) << std::endl << std::flush;

		freeze {
			std::cout << "f() = " << f(false) << std::endl << std::flush;
			std::cout << "f() = " << f(true) << std::endl << std::flush;
		}
		burst (MyBubble, b1) {
			std::cout << "inner freeze block: " << b1.reason() << std::endl << std::flush;
		}
	}
	burst (frbb::bubble, b2) {
		std::cout << "outer freeze block: " << b2.reason() << std::endl << std::flush;
	}
	return 0;
}
```

SHORT-COMINGS
--------------

1. No more than one **burst** block per **freeze** block.
2. No bubbling over type, meaning that nested **freeze** blocks will always
   catch the blown bubble.
2. Bursting bubbles variables names are available to the current code block,
   meaning that with need to track bubble names.
3. You may get seg faults if blow a bubble from a different type that is
   bursted.

FUTURE WORK
-----------

Correct all of the above.

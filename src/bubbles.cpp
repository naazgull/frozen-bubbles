#include <bubbles/bubbles.h>

bbb::BubblePtr::BubblePtr() : std::shared_ptr< bbb::BubbleCls >(new bbb::BubbleCls()) {
}
bbb::BubblePtr::BubblePtr(bbb::BubbleCls* _other) : std::shared_ptr< bbb::BubbleCls >(_other) {
}
bbb::BubblePtr::~BubblePtr() {
}

bbb::BubbleCls::BubbleCls() : __is_set(false) {
}
bbb::BubbleCls::~BubbleCls() {
}

auto bbb::BubbleCls::buffer() -> ::jmp_buf& {
	return this->__buffer;
}

auto bbb::BubbleCls::is_set() -> bool {
	return this->__is_set;
}

auto bbb::BubbleCls::set(bool _is_set) -> void {
	this->__is_set = _is_set;
}

auto bbb::BubbleCls::blow() -> void {
	if (this->__is_set) {
		longjmp(this->__buffer, 1);
	}
}

auto blow(bbb::bubble _bubble) -> void {
	_bubble->blow();
}

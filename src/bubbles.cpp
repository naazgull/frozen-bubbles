#include <frbb/frbb.h>

namespace frbb {
	pthread_key_t current_key;
	pthread_once_t current_key_once = PTHREAD_ONCE_INIT;
}
auto frbb::soak(frbb::pipe* _pipe) -> void {
	pthread_once(&frbb::current_key_once, frbb::current_key_alloc);
	pthread_setspecific(frbb::current_key, _pipe != nullptr ? _pipe : new frbb::pipe());
}
auto frbb::current_key_alloc() -> void {
	pthread_key_create(&frbb::current_key, frbb::destroy);
}
auto frbb::destroy(void* _buf) -> void {
	if (_buf != nullptr) {
		delete static_cast< frbb::pipe* >(_buf);
	}
	else {
		delete static_cast< frbb::pipe* >(pthread_getspecific(frbb::current_key));
	}
}
auto frbb::get_current() -> frbb::pipe {
	return *static_cast< frbb::pipe* >(pthread_getspecific(frbb::current_key));
}

frbb::bubble::bubble() : __bursted(0) {
}
frbb::bubble::bubble(frbb::bubble& _rhs) {
	this->__bursted = _rhs.__bursted;
}
frbb::bubble::bubble(frbb::bubble&& _rhs) {
	this->__bursted = _rhs.__bursted;
	_rhs.__bursted = 0;
}
auto frbb::bubble::bursted() -> int {
	return this->__bursted;
}
auto frbb::bubble::set_bursted(int _bursted) -> void {
	this->__bursted = _bursted;
}

frbb::BubblePipePtr::BubblePipePtr() : std::shared_ptr< frbb::BubblePipe >(new frbb::BubblePipe()) {
}
frbb::BubblePipePtr::BubblePipePtr(frbb::BubblePipe* _other) : std::shared_ptr< frbb::BubblePipe >(_other) {
}
frbb::BubblePipePtr::~BubblePipePtr() {
}

frbb::BubblePipe::BubblePipe() : __bubble(new frbb::bubble()), __prev(nullptr) {
}
frbb::BubblePipe::BubblePipe(frbb::BubblePipe* _prev) : __bubble(new frbb::bubble()), __prev(_prev) {
}
frbb::BubblePipe::~BubblePipe() {
	if (this->__bubble != nullptr) {
		delete this->__bubble;
	}
}
auto frbb::BubblePipe::get_buffer() -> ::jmp_buf& {
	return this->__buffer;
}
auto frbb::BubblePipe::get_bubble() -> frbb::bubble* {
	return this->__bubble;
}
auto frbb::BubblePipe::set_bubble(frbb::bubble* _bubble) -> void {
	if (_bubble != nullptr) {
		delete this->__bubble;
		this->__bubble = _bubble;
	}
}
auto frbb::BubblePipe::blow_pipe() -> void {
	this->__bubble->set_bursted(1);
	longjmp(this->__buffer, this->__bubble->bursted());
}
auto frbb::BubblePipe::push() -> frbb::pipe {
	frbb::pipe* _new = new frbb::pipe(new frbb::BubblePipe(this));
	frbb::soak(_new);
	return *_new;
}
auto frbb::BubblePipe::pop() -> frbb::pipe {
	frbb::pipe* _ret = new frbb::pipe(nullptr);
	this->__prev.swap(*_ret);
	frbb::destroy();
	frbb::soak(_ret);
	return *_ret;
}

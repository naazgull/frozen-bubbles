#include <frbb/frbb.h>

namespace frbb {
	pthread_key_t current_key;
	pthread_once_t current_key_once = PTHREAD_ONCE_INIT;
}
auto frbb::soak(frbb::BubblePipe* _pipe) -> void {
	pthread_once(&frbb::current_key_once, frbb::current_key_alloc);
	pthread_setspecific(frbb::current_key, _pipe != nullptr ? _pipe : new frbb::BubblePipe());
}
auto frbb::current_key_alloc() -> void {
	pthread_key_create(&frbb::current_key, frbb::destroy);
}
auto frbb::destroy(void * buf) -> void {
	delete static_cast< frbb::pipe* >(buf);
}
auto frbb::get_current() -> frbb::pipe {
	return frbb::pipe(static_cast< frbb::BubblePipe* >(pthread_getspecific(frbb::current_key)));
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
frbb::BubblePipe::~BubblePipe() {
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
	frbb::pipe _new;
	_new->__prev.reset(this);
	frbb::soak(_new.get());
	return _new;
}
auto frbb::BubblePipe::pop() -> frbb::pipe {
	frbb::pipe _ret;
	this->__prev.swap(_ret);
	frbb::soak(_ret.get());
	return _ret;
}

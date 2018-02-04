/*
Copyright (c) 2016
*/

#pragma once

#include <iostream>
#include <csetjmp>
#include <memory>

namespace frbb {

	class BubblePipePtr;
	class BubblePipe;
	typedef BubblePipePtr pipe;

	extern pthread_key_t current_key;
	extern pthread_once_t current_key_once;

	auto soak(frbb::pipe* _pipe = nullptr) -> void;
	auto current_key_alloc() -> void;
	auto destroy(void * buf = nullptr) -> void;
	auto get_current() -> frbb::pipe;

	class bubble {
	public:
		bubble();
		bubble(frbb::bubble& _rhs);
		bubble(frbb::bubble&& _rhs);

		auto bursted() -> int;
		auto set_bursted(int _bursted) -> void;

	private:
		int __bursted;
	};

	class BubblePipePtr : public std::shared_ptr< frbb::BubblePipe > {
	public:
		BubblePipePtr();
		BubblePipePtr(frbb::BubblePipe* _other);
		virtual ~BubblePipePtr();
	};

	class BubblePipe {
	public:
		BubblePipe();
		BubblePipe(frbb::BubblePipe* _prev);
		virtual ~BubblePipe();

		BubblePipe(frbb::BubblePipe& _rhs) = delete;
		BubblePipe(frbb::BubblePipe&& _rhs) = delete;
		frbb::BubblePipe& operator=(frbb::BubblePipe&) = delete;

		auto get_buffer() -> ::jmp_buf&;
		auto get_bubble() -> frbb::bubble*;
		auto set_bubble(frbb::bubble* _bubble = nullptr) -> void;
		auto blow_pipe() -> void;

		auto push() -> frbb::pipe;
		auto pop() -> frbb::pipe;
	private:
		std::jmp_buf __buffer;
		frbb::bubble* __bubble;
		frbb::pipe __prev;
	};

}

#define freeze								\
	frbb::get_current()->push();					\
	setjmp(frbb::get_current()->get_buffer());			\
	if (!frbb::get_current()->get_bubble()->bursted())
#define burst(c, b)							\
	c b = *(static_cast<c*>(frbb::get_current()->get_bubble()));	\
	frbb::get_current()->pop();					\
	if (b.bursted())
#define blow(b)								\
	{ frbb::get_current()->set_bubble(b);				\
		frbb::get_current()->blow_pipe(); }

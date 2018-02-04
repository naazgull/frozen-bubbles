/*
Copyright (c) 2016
*/

#pragma once

#include <iostream>
#include <csetjmp>
#include <memory>

namespace bbb {

	class BubblePtr;
	class BubbleCls;
	typedef BubblePtr bubble;

	class BubblePtr : public std::shared_ptr< bbb::BubbleCls > {
	public:
		BubblePtr();
		BubblePtr(bbb::BubbleCls* _other);
		virtual ~BubblePtr();
	};

	class BubbleCls {
	public:
		BubbleCls();
		virtual ~BubbleCls();
		BubbleCls(bbb::BubbleCls& _rhs) = delete;
		BubbleCls(bbb::BubbleCls&& _rhs) = delete;
		bbb::BubbleCls& operator=(bbb::BubbleCls&) = delete;

		auto buffer() -> ::jmp_buf&;
		auto is_set() -> bool;
		auto set(bool _is_set) -> void;
		auto blow() -> void;

	private:
		std::jmp_buf __buffer;
		bool __is_set;
	};
}

#define freeze(b)				\
	b->set(true);				\
	int ___err = setjmp(b->buffer());	\
	if (!___err)
#define intercept				\
	else

auto blow(bbb::bubble _bubble) -> void;

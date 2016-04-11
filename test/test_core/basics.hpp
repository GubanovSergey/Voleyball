#ifndef BASICS_HPP
#define BASICS_HPP	

#include <iostream>

namespace tests {
	using Test = int (void);
	using TestPtr = int (*)(void);
	
	//TODO imlement class testing
	//NOTE T is only standart types
	template <typename T> int test_var  //TODO replace printf with file logging
	(const T& var, const T&& expect, const char * msg_general,
	const char * msg_ok = "Passed", const char * msg_failed = "Failed") {
		using std::cout;
		if (msg_general)
			cout << msg_general << "\n";
		
		if (var == expect) {
			cout << msg_ok << "\n" << std::endl;
			return 1;
		} else {
			cout << msg_failed << "\n";
			cout << "Expected " << expect << ", Got " << var << "\n";
			cout << __LINE__ << "\n" << std::endl;
			return 0;
		}
	}
}

#endif//BASICS_HPP

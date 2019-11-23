#include <iostream>
#include <string>
#include <algorithm>
#include "stack.h"
#include "trapezoid.h"
#include "point.h"

int main() {
	containers::TStack<TTrapezoid<int>> s;
	std::string cmd;
	int index;
	std::cout << "push - to push figure to stack\n"
			  << "insert - to insert figure to stack\n"
			  << "pop - to pop figure from Stack\n"
			  << "erase - to delete figure from Stack\n"
			  << "top - to show first figure\n"
			  << "for_each - to print figures\n"
			  << "count_if - to print quantity of figures with square less then given\n"
			  << "exit - to finish execution of program\n";
	while (true) {
		std::cin >> cmd;
		if (cmd == "push") {
			std::cout << "enter coordinates\n";
			TTrapezoid<int> fig(std::cin);
			s.push(fig);
		} else if (cmd == "insert") {
			std::cout << "enter index\n";
			std::cin >> index;
			auto p = s.begin();
			try {
				s.advance(p, index);
			} catch (std::exception& err) {
				std::cout << err.what() << "\n";
				continue;
			}
			std::cout << "enter coordinates\n";
			TTrapezoid<int> fig(std::cin);
			s.insert(p, fig);
			
		} else if (cmd == "pop") {
			try {
				s.pop();
			} catch (std::exception& err) {
				std::cout << err.what() << "\n";
				continue;
			}
		} else if (cmd == "erase") {
			std::cout << "enter index\n";
			std::cin >> index;
			auto p = s.begin();
			try {
				s.advance(p, index);
			} catch (std::exception& err) {
				std::cout << err.what() << "\n";
				continue;
			}
			try {
				s.erase(p);
			} catch (std::exception& err) {
				std::cout << err.what() << "\n";
			}
			
			
		} else if (cmd == "top") {
			try {
				s.top();
			} catch (std::exception& err) {
				std::cout << err.what() << "\n";
				continue;
			}
			TTrapezoid<int> figure = s.top();
			figure.Print();

		} else if (cmd == "for_each") {
			std::for_each(s.begin(), s.end(), [] (TTrapezoid<int> tmp) {return tmp.Print();});
		} else if (cmd == "count_if") {
			int less;
			std::cout << "enter square\n";
			std::cin >> less;
			std::cout << std::count_if(s.begin(), s.end(), [less](TTrapezoid<int> t ) {return t.Square() < less;}) << "\n";

		} else if (cmd == "exit") {
			break;
		} else {
			std::cout << "wrong comand\n";
			continue;
		}
	}

}
#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>

struct Client {
	int year;
	int month;
	int code;
	int duration;
};

struct Result {
	int year;
	int month;
	int duration;
};

struct Student {
	std::string surname;
	int score;
};

#endif // !STRUCTS_H_


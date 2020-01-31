#pragma once
#include <iostream>


class CurrentOrder {


public:
	CurrentOrder();
	~CurrentOrder();
	static void SetDepth(float _depth);
	static void SetWidth(float _width);
	static void SetLength(float _length);
	static void SetTimeStart();
	static void SetTimeEnd();
	static void SetName(std::string _name);
	static void ClearValues();

private:
	static float depth, width, length;
	static std::string name;
};


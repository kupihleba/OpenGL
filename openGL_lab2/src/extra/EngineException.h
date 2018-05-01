#pragma once
#include <exception>
#include <string>

using std::string;

class EngineException : public std::exception
{
public:
	EngineException();
	~EngineException();

	EngineException(const std::string& msg) : _msg(msg) {}


	virtual const char* what() const noexcept override
	{
		return _msg.c_str();
	}

private:
	string _msg;
};


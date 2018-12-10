#ifndef _TWOSTRINGS_H_
#define _TWOSTRINGS_H_

#include <iostream>
#include <string>


class TwoStrings {
public:
	TwoStrings();

	void setPreString(const std::string&);

	void setPostString(const std::string&);

	std::string getPreString();

	std::string getPostString();

	std::string getConnectedString();

	int getConnectedLength();

private:
	std::string pre_str_;
	std::string post_str_;
};

#endif

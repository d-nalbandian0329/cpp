#include "twostrings.h"


TwoStrings::TwoStrings() : pre_str_(""), post_str_("") {
}

void TwoStrings::setPreString(const std::string& str) {
	pre_str_ = str;
}

void TwoStrings::setPostString(const std::string& str) {
	post_str_ = str;
}

std::string TwoStrings::getPreString() {
	return pre_str_;
}

std::string TwoStrings::getPostString() {
	return post_str_;
}

std::string TwoStrings::getConnectedString() {
	return pre_str_ + post_str_;
}

int TwoStrings::getConnectedLength() {
	return pre_str_.length() + post_str_.length();
}


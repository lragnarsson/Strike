/***************************************
ResourcePath.cpp

Class to do nothing on Windows or Linux, on OSX with Xcode another file with the same is used.

Written by:
Isak Wiberg
***************************************/

#include <string>

std::string resourcePath(std::string str){
	return str;
}

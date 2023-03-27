/* This file was adapted from project template provided at https://github-dev.cs.illinois.edu/cs225-sp21/rittika2-xz33-gcevans-atharva2*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>

/**
 * @brief Helper function to parse files into a string
 * @param filename - filename that will open to parse routes
 * @return a vector where the whole file is a string in 1 index
 */
std::string file_to_string(const std::string & filename) {
	std::ifstream text(filename);
	
	std::stringstream strStream;
	if (text.is_open()) {
		strStream << text.rdbuf();
	}

	return strStream.str();
}


/** 
 * Reads a file into a vector of lines
 * @param filename The file to read from
 * @return a vector containing filename's contents seperated by commas
 */
std::vector<std::string> file_to_vectorword(const std::string & filename) {
	std::ifstream text(filename);
    
	std::vector<std::string> out;

    std::string line;
    
	if (text.is_open()) {
		while (!text.eof()) {
			std::getline(text, line);
			std::stringstream ss(line);
 
			while (ss.good()) {
				std::string substr;
				std::getline(ss, substr, ',');
				out.push_back(substr);
			}
		}
	}
	return out;
} 

/** 
 * Reads a file into a vector of lines
 * @param filename The file to read from
 * @return a vector containing filename's contents seperated by lines
 */
std::vector<std::string> file_to_vectorline(const std::string & filename) {
	std::ifstream text(filename);
	std::vector<std::string> out;
    std::string line;

	if (text.is_open()) {
		while (!text.eof()) {
			std::getline(text, line);
            out.push_back(line);
		}
	}
	return out;
}

/** 
 * Reads a line into a vector of words
 * @param filename The file to read from
 * @return a vector containing the string seperated by commas
 */
std::vector<std::string> comma_sep(std::string string) {
	std::vector<std::string> out;
	std::stringstream ss(string);

	while (ss.good()) {
				std::string substr;
				std::getline(ss, substr, ',');
				out.push_back(substr);
			}

	return out;
}
/* This file was adapted from project template provided at https://github-dev.cs.illinois.edu/cs225-sp21/rittika2-xz33-gcevans-atharva2*/
#pragma once
#include <string>

// adapted from CS 225 Final Project AMA

/** 
 * Reads a file into a string
 * @param filename The file to read from 
 * @return a string containing filename's contents
 */
std::string file_to_string(const std::string & filename);

/** 
 * Reads a file into a vector of words
 * @param filename The file to read from
 * @return a vector containing filename's contents seperated by commas
 */
std::vector<std::string> file_to_vectorword(const std::string & filename);

/** 
 * Reads a file into a vector of lines
 * @param filename The file to read from
 * @return a vector containing filename's contents seperated by lines
 */
std::vector<std::string> file_to_vectorline(const std::string & filename);

/** 
 * Reads a line into a vector of words
 * @param filename The file to read from
 * @return a vector containing the string seperated by commas
 */
std::vector<std::string> comma_sep(std::string string);
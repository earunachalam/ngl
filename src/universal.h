// universally used libraries, headers, and definitions

#ifndef UNIVERSAL_H
#define UNIVERSAL_H

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <cxxabi.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <memory>
#include <omp.h>
#include <random>
#include <sstream>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>


// MACRO W (Wait)
// wait for input
#define W std::cin.get();

#define TRAP raise(SIGTRAP);

// MACRO P2S (Print To Screen)
// print the name and value of variable 'a' to the screen, preceded by the line in code in which the value was captured
#define P2S(a) std::cout << __LINE__ << ": " << #a << ": " << (a) << std::endl

// MACRO V*2S (Vector [integer/double] To Screen)
// print the name and value of vector 'a' to the screen, reshaped with dimensions (rows, cols)
// #define VI2S(a, rows, cols) if (rows != 1){std::cout << __LINE__ << ": " #a << ": \n" << Eigen::ArrayXXi::Map(&(a)[0], rows, cols) << std::endl << std::endl;} else {std::cout << __LINE__ << ": " #a << ": {" << Eigen::ArrayXXi::Map(&(a)[0], rows, cols) << "}" << std::endl;}
// #define VD2S(a, rows, cols) if (rows != 1){std::cout << __LINE__ << ": " #a << ": \n" << Eigen::ArrayXXd::Map(&(a)[0], rows, cols) << std::endl << std::endl;} else {std::cout << __LINE__ << ": " #a << ": {" << Eigen::ArrayXXd::Map(&(a)[0], rows, cols) << "}" << std::endl;}

// MACRO M2S (Message To Screen)
// print the message contained in string 'a' to the screen
#define M2S(a) std::cout << __LINE__ << ": " a << std::endl << std::endl;

// MACRO CP2S (Conditional Print To Screen)
// print the name and value of variable 'a' to the screen if condition 'cond' is fulfilled
#define CP2S(cond, a) if (cond) {P2S(a)} else {M2S("failed")};

// MACRO GC (Get Class)
#define GC(A) {int status; char * demangled = abi::__cxa_demangle(typeid(A).name(),0,0,&status); std::cout << __LINE__ << ": " #A << "\t" << demangled <<"\n";}

// MACRO LN
// print current line number
#define LN P2S(__LINE__)

// TIMING MACROS
#define INITIALIZE_TIMER() std::vector<std::clock_t> start; std::vector<double> elapsedTime;
#define TIC(num) start.push_back(std::clock()); elapsedTime.push_back(std::numeric_limits<double>::max());
#define TOC(num) elapsedTime[num] = (static_cast<double>(std::clock() - start[num]) / CLOCKS_PER_SEC); P2S(elapsedTime[num]);

// void pveci(std::vector<int> data, int rows, int cols)
// {
	
// 	if (rows*cols != data.size())
// 	{
// 		std::cout << "Invalid dimensions. size = " << data.size() << std::endl;
// 		return;
// 	}

// 	for (int row = 0; row < rows; ++row)
// 	{
// 		for (int col = 0; col < cols; ++col)
// 		{
// 			std::cout.width(6);
// 			std::cout << std::right << data.at(col + row*rows);
// 		}

// 		std::cout << std::endl;
// 	}

// 	std::cout << std::endl;
// }

// void pvecd(std::vector<double> data, int rows, int cols)
// {
	
// 	if (rows*cols != data.size())
// 	{
// 		std::cout << "Invalid dimensions. size = " << data.size() << std::endl;
// 		return;
// 	}

// 	for (int row = 0; row < rows; ++row)
// 	{
// 		for (int col = 0; col < cols; ++col)
// 		{
// 			std::cout.width(6);
// 			std::cout << std::right << data.at(col + row*rows);
// 		}

// 		std::cout << std::endl;
// 	}

// 	std::cout << std::endl;
// }


#endif
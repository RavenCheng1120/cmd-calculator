/*******
4105056005	鄭筠庭	第三次作業10/31
4105056005	Yun-Ting Cheng The Third Homework 10/31
********/
// wp_hw03_4105056005.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>                   // For stream input/output
#include <cstdlib>                    // For the exit() function
#include <cctype>                     // For the isdigit() function
#include <cstring>                    // For the strcpy() function
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

void eatspaces(char* str);            // Function to eliminate blanks
double* expr(char* str);               // Function evaluating an expression
double* term(char* str, int* index);   // Function analyzing a term
double* number(char* str, int* index); // Function to recognize a number
char* extract(char* str, int* index, int* numL); // Function to extract a substring
double* factorial(double* value);
									  
int main()
{
	char* inputcmd = new char[50];
	cout << "歡迎使用計算機，輸入load來讀取expression.txt檔，輸入type來手動輸入算式: ";
	while (cin.getline(inputcmd, 50)) {
		if (inputcmd[0] == 't' && inputcmd[1] == 'y' && inputcmd[2] == 'p' && inputcmd[3] == 'e' && inputcmd[4] == '\0') {
			cout << "選擇type模式，單按enter可以跳出。" << endl;
			for (;;)
			{
				char* buffer = new char[80];    // Input area for expression to be evaluated

				cin.getline(buffer, 80);			  // Read an input line
				eatspaces(buffer);                    // Remove blanks from input

				if (!buffer[0])                        // Empty line ends calculator
					return 0;

				cout << "\t= " << *expr(buffer)        // Output value of expression
					<< endl << endl;
				delete buffer;
			}
			break;
		}
		if (inputcmd[0] == 'l' && inputcmd[1] == 'o' && inputcmd[2] == 'a' && inputcmd[3] == 'd' && inputcmd[4] == '\0') {
			cout << "選擇load模式，讀取文字檔..." << endl;
			char* ch = new char;
			char* buffer = new char[80];
			ifstream *file = new ifstream;
			(*file).open("expression.txt", ifstream::in);
			if ((*file).is_open()) {
				while ((*file).getline(buffer, 80)){
					cout << buffer;
					eatspaces(buffer);
					cout << "  = " << *expr(buffer) << endl << endl;
				}
				(*file).close();
			}
			delete[] buffer, ch;
			break;
		}
		cout << "輸入錯誤，重新輸入: ";
	}
	//system("PAUSE");
	return 0;
}


// Function to eliminate spaces from a string
void eatspaces(char* str)
{
	int* i = new int;                              // 'Copy to' index to string
	int* j = new int;                              // 'Copy from' index to string
	*i = 0;
	*j = 0;

	while ((*(str + *i) = *(str + (*j)++)) != '\0') {  // Loop while character,copied is not \0
		if (*(str + *i) != ' ')                    // Increment i as long as
			(*i)++;                                  // character is not a space
	}
	delete i, j;
	return;
}

// Function to evaluate an arithmetic expression
double* expr(char* str)
{
	double* value = new double;                   // Store result here
	int* index = new int;                        // Keeps track of current character position
	*value = 0.0;
	*index = 0;
	*value = *term(str, index);            // Get first term

	for (;;)                              // Indefinite loop, all exits inside
	{
		switch (*(str + (*index)++))           // Choose action based on current character
		{
		case '\0':                       // We're at the end of the string
			return value;                 // so return what we have got

		case '+':                        // + found so add in the next term
			*value += *term(str, index);
			break;

		case '-':                        // - found so subtract the next term
			*value -= *term(str, index);
			break;

		default:                         // If we reach here the string is junk
			cout << endl << "錯誤的運算式!!!!" << endl;
			exit(1);
		}
	}
}

// Function to get the value of a term
double* term(char* str, int* index)
{
	double* value = new double;                       // Somewhere to accumulate 
	*value = 0.0;									 // the result
	*value = *number(str, index);          // Get the first number in the term
										 // Loop as long as we have a good operator
	while (true)
	{
		if (*(str + *index) == '*') {          
			(*index)++;						 // If it's multiply,
			*value *= *number(str, index);   // multiply by next number
		}
		else if (*(str + *index) == '/') {
			(*index)++;					  		 // If it's divide,
			*value /= *number(str, index);   // divide by next number
		}
		else if (*(str + *index) == '%') {
			(*index)++;
			*value = fmod(*value, *number(str, index));
		}
		else if (*(str + *index) == '^') {
			(*index)++;					  		 // If it's divide,
			*value = pow(*value, *number(str, index));   // divide by next number
		}
		else
			break;
	}
	return value;                        // We've finished, so return what we've got
}

// Function to recognize a number in a string
double* number(char* str, int* index)
{
	double* value = new double;            // Store the resulting value
	int* startnum = new int;
	*value = 0.0;
	*startnum = 0;

	if (*(str + *index) == '(')            // Start of parentheses
	{
		char* psubstr(nullptr);            // Pointer for substring
		(*index)++;
		*startnum += 1;
		psubstr = extract(str, index, startnum);   // Extract substring in brackets
		*value = *expr(psubstr);             // Get the value of the substring
		delete[]psubstr;                   // Clean up the free store
		return value;                      // Return substring value
	}
	else if (*(str + *index) == '[')            // Start of parentheses
	{
		char* psubstr(nullptr);            // Pointer for substring
		(*index)++;
		*startnum += 100;
		psubstr = extract(str, index, startnum);   // Extract substring in brackets
		*value = *expr(psubstr);             // Get the value of the substring
		delete[]psubstr;                   // Clean up the free store
		return value;                      // Return substring value
	}
	else if (*(str + *index) == '{')            // Start of parentheses
	{
		char* psubstr(nullptr);            // Pointer for substring
		(*index)++;
		*startnum += 10000;
		psubstr = extract(str, index, startnum);   // Extract substring in brackets
		*value = *expr(psubstr);             // Get the value of the substring
		delete[]psubstr;                   // Clean up the free store
		return value;                      // Return substring value
	}

	//是特殊計算指令
	//sin & sec & sqrt
	if (*(str + *index) == 's') {
		if (*(str + *index + 1) == 'i' && *(str + *index + 2) == 'n' && *(str + *index + 3) == '(') {
			char* psubstr(nullptr);
			(*index) += 4;
			*startnum += 1;
			psubstr = extract(str, index, startnum);
			*value = *expr(psubstr);
			delete[]psubstr;
			*value = sin(*value);
			return value;
		}
		else if (*(str + *index + 1) == 'e' && *(str + *index + 2) == 'c' && *(str + *index + 3) == '(') {
			char* psubstr(nullptr);
			(*index) += 4;
			*startnum += 1;
			psubstr = extract(str, index, startnum);
			*value = *expr(psubstr);
			delete[]psubstr;
			*value = 1/ cos(*value);
			return value;
		}
		else if (*(str + *index + 1) == 'q' && *(str + *index + 2) == 'r' && *(str + *index + 3) == 't' && *(str + *index + 4) == '(') {
			char* psubstr(nullptr);
			(*index) += 5;
			*startnum += 1;
			psubstr = extract(str, index, startnum);
			*value = *expr(psubstr);
			delete[]psubstr;
			*value = sqrt(*value);
			return value;
		}
	}
	//cos & cot & csc
	else if (*(str + *index) == 'c') {
		if (*(str + *index + 1) == 'o' && *(str + *index + 2) == 's' && *(str + *index + 3) == '(') {
			char* psubstr(nullptr);
			(*index) += 4;
			*startnum += 1;
			psubstr = extract(str, index, startnum);
			*value = *expr(psubstr);
			delete[]psubstr;
			*value = cos(*value);
			return value;
		}
		else if (*(str + *index + 1) == 'o' && *(str + *index + 2) == 't' && *(str + *index + 3) == '(') {
			char* psubstr(nullptr);
			(*index) += 4;
			*startnum += 1;
			psubstr = extract(str, index, startnum);
			*value = *expr(psubstr);
			delete[]psubstr;
			*value = 1/tan(*value);
			return value;
		}
		else if (*(str + *index + 1) == 's' && *(str + *index + 2) == 'c' && *(str + *index + 3) == '(') {
			char* psubstr(nullptr);
			(*index) += 4;
			*startnum += 1;
			psubstr = extract(str, index, startnum);
			*value = *expr(psubstr);
			delete[]psubstr;
			*value = 1 / sin(*value);
			return value;
		}
	}
	//tan
	else if (*(str + *index) == 't' && *(str + *index + 1) == 'a' && *(str + *index + 2) == 'n' && *(str + *index + 3) == '(') {
		char* psubstr(nullptr);
		(*index) += 4;
		*startnum += 1;
		psubstr = extract(str, index, startnum);
		*value = *expr(psubstr);
		delete[]psubstr;
		*value = tan(*value);
		return value;
	}
	//exp指數
	else if (*(str + *index) == 'e' && *(str + *index + 1) == 'x' && *(str + *index + 2) == 'p' && *(str + *index + 3) == '(') {
		char* psubstr(nullptr);
		(*index) += 4;
		*startnum += 1;
		psubstr = extract(str, index, startnum);
		*value = *expr(psubstr);
		delete[]psubstr;
		*value = exp(*value);
		return value;
	}
	//log10
	else if (*(str + *index) == 'l' && *(str + *index + 1) == 'o' && *(str + *index + 2) == 'g' && *(str + *index + 3) == '1'
		&& *(str + *index + 4) == '0' && *(str + *index + 5) == '(') {
		char* psubstr(nullptr);
		(*index) += 6;
		*startnum += 1;
		psubstr = extract(str, index, startnum);
		*value = *expr(psubstr);
		delete[]psubstr;
		*value = log10(*value);
		return value;
	}
	//ln
	else if (*(str + *index) == 'l' && *(str + *index + 1) == 'n' && *(str + *index + 2) == '(') {
		char* psubstr(nullptr);
		(*index) += 3;
		*startnum += 1;
		psubstr = extract(str, index, startnum);
		*value = *expr(psubstr);
		delete[]psubstr;
		*value = log(*value);
		return value;
	}

	else if (!isdigit(*(str + *index)))
	{ // There's no digits so input is junk...
		cout << endl << "錯誤的運算式!!!!" << endl;
		exit(1);
	}

	while (isdigit(*(str + *index)))       // Loop accumulating leading digits
		*value = 10 * (*value) + (*(str + (*index)++) - '0');

	// Not a digit when we get to here
	if (*(str + *index) != '.') {            // so check for decimal point
		if (*(str + (*index)) == '+' && *(str + (*index) + 1) == '+') {
			(*value)++;
			*index += 2;
		}
		else if (*(str + (*index)) == '-' && *(str + (*index) + 1) == '-') {
			(*value)--;
			*index += 2;
		}
		if (*(str + *index) == '!') {
			(*index)++;
			value = factorial(value);
			if (*(str + (*index)) == '+' && *(str + (*index) + 1) == '+') {
				(*value)++;
				*index += 2;
			}
			else if (*(str + (*index)) == '-' && *(str + (*index) + 1) == '-') {
				(*value)--;
				*index += 2;
			}
		}
		return value;
	}

	double* factor = new double;                  // Factor for decimal places
	*factor = 1.0;
	while (isdigit(*(str + (++(*index)))))   // Loop as long as we have digits
	{
		*factor *= 0.1;                     // Decrease factor by factor of 10
		*value = *value + (*(str + *index) - '0')*(*factor);   // Add decimal place
	}
	if (*(str + (*index)) == '+' && *(str + (*index) + 1) == '+') {			//檢查++
		(*value)++;
		*index += 2;
	}
	else if (*(str + (*index)) == '-' && *(str + (*index) + 1) == '-') {	//檢查--
		(*value)--;
		*index += 2;
	}
	delete factor, startnum;
	return value;                        // On loop exit we are done
}

// Function to extract a substring between parentheses 
// (requires cstring)
char* extract(char* str, int* index, int* numL)
{
	char* buffer = new char[80];                   // Temporary space for substring
	char* pstr(nullptr);                // Pointer to new string for return
	int* bufindex = new int;                // Save value for index
	*bufindex = 0;

	do
	{
		buffer[*bufindex] = *(str + *index);
		switch (buffer[*bufindex])
		{
		case ')':
			if (1 == *numL)
			{
				buffer[*bufindex] = '\0';  // Replace ')' with '\0' 
				++(*index);
				pstr = new char[++(*bufindex)];
				if (!pstr)
				{
					cout << "Memory allocation failed, program terminated.";
					exit(1);
				}
				strcpy_s(pstr, *bufindex, buffer); // Copy substring to new memory
				return pstr;                 // Return substring in new memory
			}
			else
				(*numL)--;                      // Reduce count of '(' to be matched
			break;

		case '(':
			(*numL)++;                        // Increase count of '(' to be matched
			break;

		case ']':
			if (100 == *numL)
			{
				buffer[*bufindex] = '\0';  // Replace ']' with '\0' 
				++(*index);
				pstr = new char[++(*bufindex)];
				if (!pstr)
				{
					cout << "Memory allocation failed, program terminated.";
					exit(1);
				}
				strcpy_s(pstr, *bufindex, buffer); // Copy substring to new memory
				return pstr;                 // Return substring in new memory
			}
			else
				(*numL) -= 100;                      // Reduce count of '[' to be matched
			break;

		case '[':
			(*numL) += 100;                        // Increase count of '[' to be matched
			break;

		case '}':
			if (100 == *numL)
			{
				buffer[*bufindex] = '\0';  // Replace '}' with '\0' 
				++(*index);
				pstr = new char[++(*bufindex)];
				if (!pstr)
				{
					cout << "Memory allocation failed, program terminated.";
					exit(1);
				}
				strcpy_s(pstr, *bufindex, buffer); // Copy substring to new memory
				return pstr;                 // Return substring in new memory
			}
			else
				(*numL) -= 10000;                      // Reduce count of '{' to be matched
			break;

		case '{':
			(*numL) += 10000;                        // Increase count of '{' to be matched
			break;
		}
		(*bufindex)++;
	} while (*(str + (*index)++) != '\0'); // Loop - don't overrun end of string

	cout << "錯誤的括號運用!!!!" << endl;
	exit(1);
}

//funtion for factorial
double* factorial(double* value) {
	double* f = new double(0.0);
	(*f)++;
	for ( ; *value > 0; (*value)--) {
		(*f) *= (*value);
	}
	return f;
}
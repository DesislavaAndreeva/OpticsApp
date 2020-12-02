#include <iostream>
#include <fstream>
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>
#include <cstring>
#include <vector>

using namespace std;

bool checkIfDigit(string str){
	for(int i = 0; i < str.length(); i++){
		if(isdigit(str[i]) == false)
			return false;
	}
	return true;
}

bool checkIfLetters(string string)
{
	for(int i = 0; i < string.length(); i++){
		if ( ((int)(string[i]) < 65 || ((int)(string[i]) > 90)) && ((int)(string[i]) != 32) && ( (int)(string[i]) < 97 || (int)(string[i]) > 122) ) 
            return false;
	}
	
	return true;
}

bool checkBulstat(string bulstat)
{
	/*first check*/
	if((bulstat.length() == 9) || (bulstat.length() == 10) || (bulstat.length() == 13))				
		return true;
	else
		return false;
	
	/*second check*/
	return checkIfDigit(bulstat);
}

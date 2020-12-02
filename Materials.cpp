#include <iostream>
#include <fstream>
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>
#include <cstring>
#include <vector>

#include "./include/Materials.h"
#include "./include/helpers.h"

using namespace std;

Materials::Materials() {
	width = 0;
	diopter = 0;
};

Materials::Materials(double width, double diopter, string material_type):diopter(diopter)
{
	set_width(width); 
	set_material_type(material_type); 
};
			
double Materials::get_width() { return width; };
double Materials::get_diopter() { return diopter; };
string Materials::get_material_type() { return material_type; };

void Materials::set_diopter(double entered_diopter) { diopter = entered_diopter; };

void Materials::set_material_type(string entered_material_type) 
{ 
	while(entered_material_type.length() > 35)
	{
		cout << "Max 35 characters!" << endl;
		cout << "Enter new materials: " << endl;
		getline(cin, entered_material_type);
	}
	
	material_type = entered_material_type; 
};

void Materials::set_width(double entered_width) 
{ 
	while(width < 0){
		cout << "The width cannot be negative number!" << endl;
		cout << "Enter new width: " << endl;
		cin >> entered_width;
	}
	
	width = entered_width; 
};

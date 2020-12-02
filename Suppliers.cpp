#include <iostream>
#include <fstream>
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>
#include <cstring>
#include <iomanip>
#include <bits/stdc++.h>

#include "./include/main.h"
#include "./include/Suppliers.h"
#include "./include/helpers.h"

using namespace std;

Suppliers::Suppliers() {};

Suppliers::Suppliers(string name, string bstat, string location, string phone)
{
	set_supplier_name(name);
	set_bulstat(bstat); 	
	set_phone_number(phone);
	set_location(location);
};

void Suppliers::set_location(string entered_location) 
{ 
	while(entered_location.length() > 35)
	{
		cout << "Max 35 characters!" << endl;
		cout << "Enter new location: " << endl;
		getline(cin, entered_location);
	}
	
	location = entered_location; 
};

void Suppliers::set_bulstat(string bstat) 
{ 
	while(checkBulstat(bstat) != true)
	{
		cout << "The Bulstat should be 9, 10 or 13 numbers!" << endl;
		cout << "Enter new BULSTAT: " << endl;
		getline(cin, bstat);
	}
		 
	bulstat = bstat;
};

//TODO: Better phone number validation
void Suppliers::set_phone_number(string phone) 
{ 
	while( (checkIfDigit(phone) != true) && (phone.length() != 10) )
	{
		cout << "Phone number should contain 10 numbers!" << endl;
		cout << "Enter new phone number: " << endl;
		getline(cin, phone);
	}
	
	phone_number = phone;
};

void Suppliers::set_supplier_name(string name) 
{ 
	while((checkIfLetters(name) != true) && (name.length() > 35))
	{
		cout << "Names cannot contain numbers! Max 35 characters!" << endl;
		cout << "Enter new name: " << endl;
		getline(cin, name);
   } 
   
   supplier_name = name;
};

string Suppliers::get_bulstat() { return bulstat; };
string Suppliers::get_location() { return location; };
string Suppliers::get_supplier_name() { return supplier_name; };
string Suppliers::get_phone_number() { return phone_number; };

// Insertion operator
/*Overload operator '<<' to write the Suppliers object in file*/
ofstream& operator<<(ofstream& os, const Suppliers& s)
{
	// write out individual members of s with an end of line between each one and # delimiter
	os << "#" << s.supplier_name << "#" << s.bulstat << "#" <<  s.location << "#" << s.phone_number << '\n';
	return os;
}

// Extraction operator
/*Overload operator '>>' to read the object of type Suppliers in file*/
/*ifstream& operator>>(ifstream& is, Suppliers& s)
{
	// read in individual members of s
	is >> s.supplier_name >> s.bulstat >> s.location >> s.phone_number;
	return is;
}*/

/*Overload operator '<<' to print the Suppliers object*/
ostream& operator<<(ostream &os, Suppliers s)
{
	printElement(s.get_supplier_name(), 35);
	printElement(s.get_bulstat(), 35);
	printElement(s.get_location(), 35);
	printElement(s.get_phone_number(), 35);
	
	return os;
};

int Suppliers::create_new_supplier_from_ui(Suppliers *s)
{	
	 string name;  
     string bulstat;
     string location;
     string phone;
     
     cout << "Enter suppliers name: " << endl;
     cin.clear();
	 cin.ignore(numeric_limits<streamsize>::max(),'\n');
     getline(cin, name);
     s->set_supplier_name(name);
     
     cout << "Enter suppliers bulstat: " << endl;
     getline(cin, bulstat);
     s->set_bulstat(bulstat);
     
     cout << "Enter suppliers location: " << endl;
     getline(cin, location);
     s->set_location(location);
     
     cout << "Enter suppliers phone number: " << endl;
     getline(cin, phone);
     s->set_phone_number(phone);
     
	 //Bulstat should be unique in the DB
     if(check_if_supplier_exists(bulstat))
		return 1;
       
	 return 0;
};

/*Overload operator '=' to copy one object of type Suppliers to another*/
Suppliers& Suppliers::operator = (Suppliers s){
	bulstat = s.bulstat;
	supplier_name = s.supplier_name;
	phone_number = s.phone_number;
	location = s.location;
	return *this;
}

#include <iostream>
#include <fstream>
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>
#include <cstring>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>

#include "./include/main.h"
#include "./include/Optics.h"
#include "./include/Materials.h"
#include "./include/helpers.h"

using namespace std;
	
Optics::Optics() : Materials(){
	price = 0;
};
		
Optics::Optics(string type, double price, double width, double diopter, string material_type): Materials(width, diopter, material_type)
{
	set_type(type); 
	set_price(price);  
};

Optics::Optics(string type, double price, double width, double diopter, string material_type, string bulstat): Materials(width, diopter, material_type)
{
	set_type(type); 
	set_price(price);

	if(check_if_supplier_exists(bulstat))
		supplier = get_supplier_from_local_db(bulstat);
	else
		cout << "There is no such supplier in the DB!" << endl;
};

Optics::Optics(string type, double price, double width, double diopter, string material_type, Suppliers supplier) : Materials(width, diopter, material_type), supplier(supplier)
{
	set_type(type); 
	set_price(price); 
};
		
string Optics::get_type() { return type; };
double Optics::get_price() { return price; };

void Optics::set_type(string entered_type) 
{ 
	while(entered_type.length() > 35)
	{
		cout << "Max 35 characters!" << endl;
		cout << "Enter new type: " << endl;
		getline(cin, entered_type);
	}
	
	type = entered_type; 
};

void Optics::set_price(double entered_price) 
{ 
	while(entered_price < 0)
	{
		cout << "The price cannot be negative number!" << endl;
		cout << "Enter new price: " << endl;
		cin >> entered_price;
	} 
	
	price = entered_price;
};

/*Overload operator '=' to copy one object of type Optics to another*/
Optics& Optics::operator = (Optics o){
	type = o.type;
	price = o.price;
	supplier = o.supplier;
	return *this;
}

/*Overload operator '<<' to write the Optics object into file*/
ofstream& operator<<(ofstream& os, Optics& o)
{
	os << "#" << o.get_type() << "#" << o.get_price() << "#" <<  o.get_material_type() << "#" << o.get_width() << "#" << o.get_diopter() << "#" << o.supplier.get_bulstat() << endl;
	return os;
}

/*Overload operator '<<' to print the Optics object*/
ostream& operator<< (ostream &os, Optics ob1)
{
	const char separator = ' ';
	
	printElement(ob1.get_type(), 35);
	printElement(ob1.get_material_type(), 35);	
	cout << left << setw(10) << setfill(separator) << ob1.get_diopter();
    cout << left << setw(10) << setfill(separator) << ob1.get_width();
    cout << left << setw(10) << setfill(separator) << ob1.get_price();    
    printElement(ob1.supplier.get_bulstat(), 35);

	return os;
};

int Optics::create_new_optics_from_ui(Optics *s)
{	
	 double diopter;
	 double width;
	 double price;
	 string bulstat;
	 string optics_type;
	 string material_type;
	 
	 cout << "Enter optics type: " << endl;
     cin.clear();
	 cin.ignore(numeric_limits<streamsize>::max(),'\n');
     getline(cin, optics_type);
     s->set_type(optics_type);
	 
	 cout << "Enter the material type: " << endl;
     getline(cin, material_type);
     s->set_material_type(material_type);
	 
	 cout << "Enter the optics price: " << endl;
     cin >> price;
     s->set_price(price);
      
	 cout << "Enter material width: " << endl;
     cin >> width;
     s->set_width(width);
	 
	 cout << "Enter the diopter: " << endl;
     cin >> diopter;
     s->set_diopter(diopter);
     
     cout << "Enter suppliers BULSTAT: " << endl;
     getline(cin, bulstat);
     getline(cin, bulstat);
     s->supplier.set_bulstat(bulstat);
     
     if(check_if_optics_exists(s))
		return 1;
     
	 //Create new optics only if the supplier with the entered Bulstat exists in the DB
     if(check_if_supplier_exists(bulstat))
     {
		s->supplier = get_supplier_from_local_db(bulstat);
	 }
	 else
	 {
		cout << "There is no such supplier in the DB! Enter valid supplier!" << endl;
		return 1;
	 }
	
	 return 0;
};

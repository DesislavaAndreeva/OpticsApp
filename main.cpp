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
#include "./include/Suppliers.h"
#include "./include/Materials.h"
#include "./include/Optics.h"
#include "./include/main.h"

using namespace std;

/*Local DB*/
vector <Suppliers> v_suppliers;
vector <Optics> v_optics;

/*using manipulators to format the output to print the DB as table*/
void printElement(string text, int width)
{
	const char separator = ' ';
	
    cout << left << setw(width) << setfill(separator) << text;
}

/*By given bulstat to find how many optics entries he has in the DB*/
int get_optics_count(string bulstat)
{
	int count = 0;
	
	for(int i = 0; i < v_optics.size(); i++)
	{
		if(!bulstat.compare(v_optics[i].supplier.get_bulstat()))
			count++;
	}
	
	return count;
}

bool check_if_supplier_exists(string bulstat)
{
	for(int i = 0;  i < v_suppliers.size(); i++)
	{
		if(!bulstat.compare(v_suppliers[i].get_bulstat()))
			return true;
	}
	
	return false;
}

Suppliers get_supplier_from_local_db(string bulstat)
{
	for(int i = 0;  i < v_suppliers.size(); i++)
	{
		if(!bulstat.compare(v_suppliers[i].get_bulstat()))
			return v_suppliers[i];
	}
	
	return Suppliers();
}

bool check_if_optics_exists(Optics *op)
{
	for(int i = 0; i < v_optics.size(); i++)
	{
		if( (op->get_type() == v_optics[i].get_type())
		   && (op->get_price() == v_optics[i].get_price())
		   && (op->get_width() == v_optics[i].get_width())
		   && (op->get_diopter() == v_optics[i].get_diopter())
		   && (!op->get_material_type().compare(v_optics[i].get_material_type()))
		   && (!op->supplier.get_bulstat().compare(v_optics[i].supplier.get_bulstat()))
		  )
		{
			return true;
		}
	}
	
	return false;
}

/****************************************************
* Function Name: read_info_from_file() 
* Input        : The name of the file
* Logic        : Read the file line by line
* Note         : Used for testing purposes
*****************************************************/
void read_info_from_file(string file_name)
{
	string line;
	ifstream ifs(file_name);

	while(getline(ifs, line)){
	   cout << line << '\n'; 
	}
}

void write_suppliers_info_to_file(Suppliers s)
{
	ofstream ofs("Suppliers.txt", ios_base::app);
	ofs << s; 
	ofs.close();
}

void write_optics_info_to_file(Optics opt)
{
	ofstream ofs("Optics.txt", ios_base::app);
	ofs << opt; 
	ofs.close();
}

/*The following three functions below are used to format and print the DBs as tables*/
void show_suppliers_info()
{
	if(v_suppliers.size() == 0)
		return;
	
	cout << endl << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
	printElement("Supplier name:", 35);
	printElement("Supplier BULSTAT:", 35);
	printElement("Supplier location:", 35);
	printElement("Supplier phone number:", 35);
	cout << endl << "===============================================================================================================================" << endl;
	
	for(int i = 0;  i < v_suppliers.size(); i++)
		cout << v_suppliers[i] << endl;
	
	cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void show_optic_header()
{
	cout << endl << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
	printElement("Id:", 10);
	printElement("Optic type:", 35);
	printElement("Materials:", 35);
	printElement("Diopter:", 10);
	printElement("Width:", 10);
	printElement("Price:", 10);
	printElement("Supplier BULSTAT:", 35);
	cout << endl << "===============================================================================================================================" << endl;
}

void show_optics_info()
{
	const char separator = ' ';
	
	if(v_suppliers.size() == 0)
		return;
	
	show_optic_header();
	
	for(int i = 0; i < v_optics.size(); i++)
	{
		cout << left << setw(10) << setfill(separator) << i;
		cout << v_optics[i] << endl;
	}
	
	cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
}

/*****************************************************************
* Function Name: process_choice()
* Input        : string choice - chosen supplier's bulstat;
* 				 vector<double> order_prices - list with the
				 prices of all product that the user will order;
				 
* Return       : true - the user want to continue ordering;
* 				 false - user completed the order; 
* Logic        : If the user entered "exit" calculate the cost
				 of the order; else show the optics of the chosen
				 supplier;
*****************************************************************/
bool process_choice(string choice, vector<double> order_prices)
{
	double order_price = 0.0;
	const char separator = ' ';
	
	if(!choice.compare("exit"))
	{
		for(int i = 0; i < order_prices.size(); i++)
			order_price += order_prices[i];
			
		if(order_price > 0)
		   cout << endl << "The total cost of your order is:" << order_price << " lv" << endl;
		
		return false;
	}
	else
	{
		if(get_optics_count(choice))
		{
			show_optic_header();
			
			for(int i = 0; i < v_optics.size(); i++)
			{
				if(!choice.compare(v_optics[i].supplier.get_bulstat()))
				{
					cout << left << setw(10) << setfill(separator) << i;
					cout << v_optics[i] << endl;
				}
			}
			
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	
	return true;
}

/*************************************************************
* Function Name: check_optics_id()
* Input        : The bulstat of the chosen supplier;
				 The id of the chosen product/optics;
				 
* Return       : true - entered id is correct;
				 false - entered id is not correct;
				 
* Logic        : The id's of the products/optics from one 
				 supplier are not consistently ordered. This 
				 function finds out if the entered id is 
				 relevant for the chosen supplier;
**************************************************************/
bool check_optics_id(string bulstat, int id)
{		
	for(int i = 0; i < v_optics.size(); i++)
	{
		if(!bulstat.compare(v_optics[i].supplier.get_bulstat()))
		{
			if(i == id)
				return true;
		}
	}
	
	return false;
}

/****************************************************************
* Function Name: order_products_from_supplier()
* Input        : The bulstat of the chosen supplier;
* Return       : The final cost of the ordered items from this
				 supplier;
* Logic        : If supplier has products, allow user to add as
				 many as he want, until he presses "-1" which 
				 indicates you should calculate the final 
				 cost of the added products and return it;
*****************************************************************/
double order_products_from_supplier(string bulstat)
{
	int id = 0; 
	int product_count = 0;
	double order_price = 0.0;
	double product_price = 0.0;
	vector<double> orders;
	
	if(!get_optics_count(bulstat))
	{
		cout << "This supplier doesn't have products yet!" << endl;
		return 0;
	}	
		
	while(1)
	{
		cout << endl << "Enter the ID of the product/s you want to order!"  << endl;
		cout << "Enter '-1' if you want to complete the order from this supplier!"  << endl;
		cin >> id;
		
		if(id != -1)
		{		
			if( id < 0 || !check_optics_id(bulstat, id))
			{
				cout << "Chosen ID is wrong!" << endl;
				continue;
			}
			
			cout << endl << "How many pieces of this product would you like to order?"  << endl;
			cin >> product_count;
			
			product_price = v_optics.at(id).get_price();
			order_price = product_price * product_count;
			orders.push_back(order_price);
			order_price = 0.0;
		}
		else
			break;
	}
	
	for(int i = 0; i < orders.size(); i++)
		order_price += orders[i];
			
	return order_price;
}

/*********************************************************
* Function Name: MakeOrders()
* Description  : Handles the case of ordering products
				 until the user presses "exit". Keep the
				 costs of all the prices from different 
				 suppliers which will be used at the end 
				 to calculate the final cost of the order;
**********************************************************/
void MakeOrders()
{
	string choice; 
	double order_price = 0.0;
	vector<double> order_prices;
	
	show_suppliers_info();
		
	while(1)
	{
		cout << endl << "Enter 'exit' if you want to return to the main menu!"  << endl;
		cout << "Enter supplier BULSTAT to view his products:"  << endl;	
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');	
		}	
		getline(cin, choice);
				
		if(!process_choice(choice, order_prices))
			return;
			
		order_price = order_products_from_supplier(choice);
		order_prices.push_back(order_price);	
	}
	
	return;
}

/*******************************************************************
* Function Name: enterSuppliersInfo()
* Description  : Handles the case of adding new supplier in the DB 
* Logic        : Get the data from user input, create new Supplier 
				 object, add it in the local DB and into the file;
				 Checks for duplicated bulstats;
* Notes        : NONE
********************************************************************/
void enterSuppliersInfo()
{ 	 
	Suppliers supplier;
	int err = supplier.create_new_supplier_from_ui(&supplier);

	if(!err)
	{
		v_suppliers.push_back(supplier);
		write_suppliers_info_to_file(supplier);
		
		//used for testing
		//read_info_from_file("Suppliers.txt");
	}
	else
		cout << "Supplier with this bulstat already exists!" << endl;
}

/****************************************************************
* Function Name: enterOpticsInfo()
* Description  : Handles the case of adding new optics in the DB
* Logic        : Get the data from user input, create new Optics 
				 object, add it in the local DB and into the file; 
				 Checks for duplicated entries and exsisting 
				 suppliers;
* Notes        : NONE
******************************************************************/
void enterOpticsInfo()
{
   Optics optic;		 
   int err = optic.create_new_optics_from_ui(&optic);

   if(!err)
   {
	   v_optics.push_back(optic);
	   write_optics_info_to_file(optic);
	   
	   //used for testing
	   //read_info_from_file("Optics.txt");
   }
   else
	  cout << "Couldn't create optic entry!" << endl;
}

/***************************************************************
* Function Name: convert_line_to_obj()
* Description  : Function that takes line read from file, 
				 splits the data, create and add an object 
				 (Supplier/Optics) in the local DB, depending 
				 on the given type (SUPPLIER_OBJ/OPTICS_OBJ);
* Input        : string line - line read from file;
* 				 int type - type of object to create;
****************************************************************/
void convert_line_to_obj(string line, int type)
{
	stringstream check(line);
	vector <string> obj_elements; 
	string obj_element; 
	string::size_type sz;
	
	while(getline(check, obj_element, '#'))
	   obj_elements.push_back(obj_element); 
	
	//https://stackoverflow.com/questions/5685471/error-jump-to-case-label
	switch(type)
	{
		case SUPPLIER_OBJ:
		{
			/*Indexes*/
			/*1 - name; 2 - bulstat; 3 - location; 4 - phone_number;*/
			Suppliers supplier(obj_elements[1], obj_elements[2], obj_elements[3], obj_elements[4]);
			v_suppliers.push_back(supplier);
		}
		break;
		
		case OPTICS_OBJ:
		{
			/*Indexes*/
			/*1 - type; 2 - price; 3 - material type; 4 - width; 5 - diopter; 6 - supplier name;*/
			Optics optic(obj_elements[1], stod (obj_elements[2], &sz), stod (obj_elements[4], &sz), stod (obj_elements[5], &sz), obj_elements[3], obj_elements[6]);
			v_optics.push_back(optic);
		}
		break;
			
		default:
			break;
	}
}

void read_startup_db(string file_name, int type)
{
	string line;
	ifstream ifs(file_name);
	    	
	while(getline(ifs, line))	
	   convert_line_to_obj(line, type);	
}

void print_menu()
{
	cout << "Menu: "  << endl;
	cout << "Press '1' to enter new supplier in the DB! " << endl;
    cout << "Press '2' to enter optics information in the DB! " << endl;
    cout << "Press '3' to order materials from a supplier!" << endl;
    cout << "Press '4' to view full db!" << endl;
    cout << "Press '5' to exit the program! " << endl;
}

int main()
{	
    int choice = 0;
	read_startup_db("Suppliers.txt", SUPPLIER_OBJ);
	read_startup_db("Optics.txt", OPTICS_OBJ);
	
	while(1)
	{
		print_menu();
	    cout << endl << "Enter the next operation you would like to proceed: "  << endl;
	    cin >> choice; 
	    
		switch ( choice ) {
			   case 1:
					enterSuppliersInfo();
					break;
					
			   case 2:
					enterOpticsInfo();
					break;
					
			   case 3:
					MakeOrders();
					break;
				
				case 4:
					show_suppliers_info();
					show_optics_info();
					break;
						
			   case 5:
					exit(1);
					break;
					
				default:
					break;
		}
  }
    	
	return 0;
}

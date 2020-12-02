#ifndef SUPPLIER_H
#define SUPPLIER_H

using namespace std;

class Suppliers{
	protected:
		string bulstat;
		string supplier_name;
		string phone_number;
		string location;
	public:
		/*Constructors*/
		Suppliers();
		Suppliers(string name, string bulstat, string location, string phone);	
		
		/*Getters*/
		int get_id();
		string get_bulstat();
		string get_supplier_name();
		string get_phone_number();
		string get_location();
		
		/*Setters*/
		void set_bulstat(string bstat);		
		void set_phone_number(string phone);		
		void set_supplier_name(string name);		
		void set_location(string entered_location);
		
		int create_new_supplier_from_ui(Suppliers *s);
		
		friend bool checkIfDigit(string str);
		friend bool checkBulstat(string bulstat);
		friend bool checkIfLetters(string string);
		friend ostream& operator<<(ostream&, Suppliers s);
		friend ifstream& operator>>(ifstream& is, Suppliers& s);
		friend ofstream& operator<<(ofstream& os, const Suppliers& s);	
		Suppliers& operator = (Suppliers);
};

#endif

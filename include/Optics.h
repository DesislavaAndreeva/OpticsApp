#ifndef OPTICS_H
#define OPTICS_H

#include "Suppliers.h"
#include "Materials.h"

using namespace std;

class Optics: public Materials{
    private:
		string type;
		double price;
	public:	
		Suppliers supplier;
		
		/*Constructors*/
		Optics ();
		Optics (string type, double price, double width, double diopter, string materal_type);
		Optics(string type, double price, double width, double diopter, string material_type, string bulstat);
		Optics (string type, double price, double width, double ddiopter, string material_type, Suppliers s);
		
		/*Getters*/
		string get_type();
		double get_price();
		
		/*Setters*/
		void set_type(string entered_type);
		void set_price(double entered_price);
		
		Optics& operator = (Optics);
		friend ostream& operator<<(ostream&, Optics ob1);
		friend ofstream& operator<<(ofstream& os, Optics& o);
		
		int create_new_optics_from_ui(Optics *s);
};

#endif

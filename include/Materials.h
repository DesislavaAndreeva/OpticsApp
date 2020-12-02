#ifndef MATERIAL_H
#define MATERIAL_H

using namespace std;

class Materials{
	private:
		double width;
		double diopter;
		string material_type;
	public:
		/*Constructors*/
		Materials();
		Materials(double width, double diopter, string material_type);					
		
		/*Getters*/
		double get_width();
		double get_diopter();
		string get_material_type();
		
		/*Setters*/
		void set_width(double entered_width);
		void set_diopter(double entered_diopter);
		void set_material_type(string entered_material_type);
};

#endif

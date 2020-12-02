#ifndef MAIN_H
#define MAIN_H

#include "Optics.h"
#include "Suppliers.h"

using namespace std;

#define OPTICS_OBJ 1
#define SUPPLIER_OBJ 2
#define MAX_FIELDS 4

void printElement(string t, int width);
int get_optics_count(string bulstat);
bool check_if_optics_exists(Optics *op);
bool check_if_supplier_exists(string bulstat);
Suppliers get_supplier_from_local_db(string bulstat);

#endif

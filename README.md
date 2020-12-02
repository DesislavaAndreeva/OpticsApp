# OpticsApp
C++ application that supports information about optics, suppliers and their products

# General info

University evaluation project

# Description

This is an application that supports information about optics suppliers and their products. The suppliers information consists of name, bulstat, 
location and phone number. Each supplier can deliver one or more optics, which is characterized by type, thickness, diopter and name of the material. 
The application allows entering new supplier/optics in the DB, ordering products from different suppliers and calculating the total price of the order. 
It stores the data in a file, but supports local DB for faster work. 

# Details

### The aplication need to:

 * Ensure the creation and maintenance of persistent database (file);
 * Perform initial loading of data in local DB from file (if exists) at startup;
 * Allow ordering products from different suppliers and calculating the final price;
 * Perform validation of the input data;
 
# Compile

```
make clean 
make
```
 
 # Run  
 ./optics
 

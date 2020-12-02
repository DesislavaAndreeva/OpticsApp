CC=gcc
ODIR=./
LIBS=-lstdc++

_OBJ = main.o helpers.o Suppliers.o Materials.o Optics.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(LIBS)

optics: $(OBJ)
	gcc -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

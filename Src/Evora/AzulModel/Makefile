LIBDIR = lib

all:
	gcc -c *.cpp
	mkdir $(LIBDIR)
	ar rvs $(LIBDIR)/AzulModel.a *.o
	rm *.o
clean:
	rm $(LIBDIR)/AzulModel.a
	rmdir $(LIBDIR)
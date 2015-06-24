# Targets & general dependencies
PROGRAM = xsim
HEADERS = xis.h xcpu.h 
OBJS = xsim.o xcpu.o 
ADD_OBJS = 
GOLD = xsim_gold 

# compilers, linkers, utilities, and flags
CC = gcc
CFLAGS = -Wall -g
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(CFLAGS) -o $@ 

# implicit rule to build .o from .c files
%.o: %.c $(HEADERS)
	$(COMPILE) -c -o $@ $<


# explicit rules
all: xld xas xcc xmkos $(GOLD) xsim 

$(PROGRAM): $(OBJS) $(ADD_OBJS)
	$(LINK) $(OBJS) $(ADD_OBJS)

xsim_gold: libxsim.a 
	$(LINK) libxsim.a

xas: xas.o xreloc.o
	$(LINK) xas.o xreloc.o

xld: xld.o xreloc.o
	$(LINK) xld.o xreloc.o

xmkos: xmkos.o xreloc.o
	$(LINK) xmkos.o xreloc.o

xcc: xcc.o 
	$(LINK) xcc.o
	
lib: xsim_gold.o xcpu_gold.o
	 ar -r libxsim.a xsim_gold.o xcpu_gold.o 

clean:
	rm -f *.o *.xo *.xx $(PROGRAM) xas xld xcc xmkos $(GOLD)

zip:
	make clean
	rm -f xsim.zip
	zip xsim.zip *

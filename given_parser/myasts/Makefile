CFLAGS=-Wall -pedantic -std=c++14 -g #-Werror
LIBS=-lfmt
TYPECHECKER_OBJS=TypeChecker.o Parser.o
AST_OBJS=Program.o Declaration.o StructType.o TypeDeclaration.o Function.o
all: typeChecker

typeChecker: $(AST_OBJS) $(TYPECHECKER_OBJS)
	g++ $(CFLAGS) -o typeChecker $(TYPECHECKER_OBJS) $(AST_OBJS) $(LIBS)

.cpp.o: 
	g++ -c $(CFLAGS) $< -o $@
#%.o: %.cpp %.hpp 
#	g++ -c $(CFLAGS) $< -o $@ $(LIBS)

cleano:
	rm -rf *.o

clean:
	rm -f *.o typeChecker

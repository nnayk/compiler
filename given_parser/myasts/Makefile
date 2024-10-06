CFLAGS=-Wall -pedantic -std=c++20 -g #-Werror
LIBS=-lfmt
TYPECHECKER_OBJS=TypeChecker.o Parser.o
AST_OBJS=Program.o Declaration.o StructType.o TypeDeclaration.o Function.o \
BlockStatement.o AbstractStatement.o AssignmentStatement.o LvalueId.o \
LvalueIndex.o LvalueDot.o InvocationExpression.o DotExpression.o \
AbstractExpression.o IndexExpression.o UnaryExpression.o BinaryExpression.o \
IdentifierExpression.o IntegerExpression.o TrueExpression.o FalseExpression.o \
NewArrayExpression.o NewExpression.o
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

CFLAGS=-Wall -pedantic -std=c++20 -g -Werror
LIBS=-lfmt
TYPECHECKER_OBJS=TypeChecker.o Parser.o
AST_OBJS=Program.o Declaration.o TypeDeclaration.o Function.o \
BlockStatement.o AbstractStatement.o AssignmentStatement.o LvalueId.o \
LvalueDot.o InvocationExpression.o DotExpression.o \
AbstractExpression.o IndexExpression.o UnaryExpression.o BinaryExpression.o \
IdentifierExpression.o IntegerExpression.o TrueExpression.o FalseExpression.o \
NewExpression.o PrintStatement.o ConditionalStatement.o \
WhileStatement.o DeleteStatement.o ReturnStatement.o ReturnEmptyStatement.o \
InvocationStatement.o Env.o ReadExpression.o Register.o Bblock.o Lvalue.o \
NullExpression.o Label.o 

CFG_OBJS=CfgProg.o CfgFunc.o 

all: cfg

cfg: $(AST_OBJS) $(TYPECHECKER_OBJS) $(CFG_OBJS)
	g++ $(CFLAGS) -o cfg $(TYPECHECKER_OBJS) $(AST_OBJS) $(CFG_OBJS) $(LIBS)

#typechecker: $(AST_OBJS) $(TYPECHECKER_OBJS)
#	g++ $(CFLAGS) -o typechecker $(TYPECHECKER_OBJS) $(AST_OBJS) $(LIBS)

.cpp.o: 
	g++ -c $(CFLAGS) $< -o $@
#%.o: %.cpp %.hpp 
#	g++ -c $(CFLAGS) $< -o $@ $(LIBS)

cleano:
	rm -rf *.o

clean:
	rm -f *.o typechecker cfg

all: GenerateStateMachine.o ExampleStateMachine.o
	g++ GenerateStateMachine.o  -o GenerateStateMachine
	g++ ExampleStateMachine.o -o ExampleStateMachine

ExampleStateMachine.o: ExampleStateMachine.cpp ExampleStateMachine.h ExampleStateMachine.dot
	g++ -I . -c ExampleStateMachine.cpp
 

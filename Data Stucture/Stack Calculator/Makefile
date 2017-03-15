all: $(patsubst %.java, %.class, $(wildcard *.java))

%.class: %.java
	javac $< -Xdiags:verbose -Xlint:unchecked

.PHONY: run test clean
run: all
	@java CalculatorTest

test: all
	java CalculatorTest < tests/in1.txt > tests/actual1.txt
	diff tests/actual1.txt tests/out1.txt
	java CalculatorTest < tests/in2.txt > tests/actual2.txt
	diff tests/actual2.txt tests/out2.txt

clean:
	@rm -f *.class tests/actual*.txt

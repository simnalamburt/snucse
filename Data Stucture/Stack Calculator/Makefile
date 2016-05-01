all: $(patsubst %.java, %.class, $(wildcard *.java))

%.class: %.java
	javac $< -Xdiags:verbose -Xlint:unchecked

.PHONY: run clean
run: all
	@java CalculatorTest

clean:
	@rm -f *.class

all: $(patsubst %.java, %.class, $(wildcard *.java)) test/AssignmentGuide.class

%.class: %.java
	javac $<

clean:
	@rm -f *.class test/*.class

all:
	@bash -c '\
	  g++ print.cpp -o print && \
	  ./print \
	' && echo "Program execution successful." || echo "Program execution failed."

clue_a:
	g++ ./clue_to_you/a.cpp -o ./clue_to_you/a
	./clue_to_you/a

clue_b:
	g++ ./clue_to_you/b.cpp -o ./clue_to_you/b
	./clue_to_you/b

clue_c:
	g++ ./clue_to_you/c.cpp -o ./clue_to_you/c
	./clue_to_you/c

clue_d:
	g++ ./clue_to_you/d.cpp -o ./clue_to_you/d
	./clue_to_you/d

print_v2:
	g++ print_v2.cpp -o print_v2
	./print_v2

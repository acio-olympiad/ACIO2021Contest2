.PHONY: all clean

all:
	python3 makecases.py
	bash ./make-output.sh
	-rm Tkgen
	-rm tmp.txt

clean:
	-rm *.in *.out
	-rm sol

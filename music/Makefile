.PHONY: default clean

default: triforce.pat OvertureOfSages.pat

%.pat: %.aseq
	$(PYTHON3) ../toolchain/create_patch.py --full $< $@

clean:
	rm -f *.pat
	

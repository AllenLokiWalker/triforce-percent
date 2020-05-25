.PHONY: default clean

default: triforce.pat

%.pat: %.aseq
	$(PYTHON3) ../toolchain/create_patch.py --full $< $@

clean:
	rm triforce.pat
	

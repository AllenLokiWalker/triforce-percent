TEXTURES = triforce.rgba32.pat

ZAP2 = ../toolchain/ZAP2/ZAP2.out
CREATE_PATCH = $(PYTHON3) ../toolchain/create_patch.py

.PHONY: default clean

.PRECIOUS: %.rgba32 %.rgb5a1 %.ia8 %.ci8 %.i4 %.ia4

default: $(TEXTURES)

clean:
	rm -f *.rgba32 *.rgb5a1 *.ia8 *.ci8 *.i4 *.ia4 *.pat

%.pat: %
	$(CREATE_PATCH) --full $< $@

%.rgba32: %.rgba32.png
	$(ZAP2) btex -tt rgba32 -i $< -o $@

%.rgb5a1: %.rgb5a1.png
	$(ZAP2) btex -tt rgba5a1 -i $< -o $@

%.ia8: %.ia8.png
	$(ZAP2) btex -tt ia8 -i $< -o $@

%.ci8: %.ci8.png
	$(ZAP2) btex -tt ci8 -i $< -o $@

%.i4: %.i4.png
	$(ZAP2) btex -tt i4 -i $< -o $@

%.ia4: %.ia4.png
	$(ZAP2) btex -tt ia4 -i $< -o $@

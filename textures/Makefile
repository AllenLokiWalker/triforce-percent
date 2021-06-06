TEXTURES = triforce.rgba32.pat ddn.ia8.inc dup.ia8.inc

ZAPD = ../toolchain/ZAP2/ZAPD.out
CREATE_PATCH = $(PYTHON3) ../toolchain/create_patch.py

.PHONY: default clean

.PRECIOUS: %.rgba32.inc %.rgb5a1.inc %.ia8.inc %.ci8.inc %.i4.inc %.ia4.inc

default: $(TEXTURES)

clean:
	rm -f *.rgba32.inc *.rgb5a1.inc *.ia8.inc *.ci8.inc *.i4.inc *.ia4.inc *.pat

%.pat: %
	$(CREATE_PATCH) --full $< $@

%.rgba32.inc: %.rgba32.png
	$(ZAPD) btex -tt rgba32 -i $< -o $@

%.rgb5a1.inc: %.rgb5a1.png
	$(ZAPD) btex -tt rgba5a1 -i $< -o $@

%.ia8.inc: %.ia8.png
	$(ZAPD) btex -tt ia8 -i $< -o $@

%.ci8.inc: %.ci8.png
	$(ZAPD) btex -tt ci8 -i $< -o $@

%.i4.inc: %.i4.png
	$(ZAPD) btex -tt i4 -i $< -o $@

%.ia4.inc: %.ia4.png
	$(ZAPD) btex -tt ia4 -i $< -o $@

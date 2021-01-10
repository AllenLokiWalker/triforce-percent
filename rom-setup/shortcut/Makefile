.PHONY: default clean

BUILDDIR = ../../build-shortcut
BUILDRTL = $(BUILDDIR)/oot_build.rtl

default: $(BUILDDIR)/tf-shortcut.z64
	
$(BUILDDIR)/tf-shortcut.z64: $(BUILDDIR)/update.txt ../../toolchain/zzrtl/oot_build.rtl
	cp ../../toolchain/zzrtl/oot_build.rtl $(BUILDRTL)
	sed -i 's/build.z64/tf-shortcut.z64/g' $(BUILDRTL)
	sed -i 's/rhstatics(rom);//g' $(BUILDRTL)
	$(ZZRTL) $(BUILDRTL)

clean:
	rm -rf $(BUILDDIR)/tf-shortcut.z64

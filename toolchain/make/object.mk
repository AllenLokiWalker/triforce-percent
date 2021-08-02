CCFLAGS += -Wno-incompatible-pointer-types -Wno-missing-braces

$(OBJECTNAME).elf: $(OBJECTOBJS)
	$(LD) $(LDFLAGS) -T $(PROJECT_DIR)/actor/object.ld -Map $(OBJECTNAME).map -o $@ $^

zobj.zobj: $(OBJECTNAME).elf
	$(OC) $(OCFLAGS) $< $@
	
%.out.ld: %.map
	$(PYTHON3) $(PROJECT_DIR)/toolchain/ldout.py $< $@

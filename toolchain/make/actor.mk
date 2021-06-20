NOVL = novl
YAZ0 = ../../toolchain/yaz0/yaz0_encode
BASEADDR ?= 0x80800000

ZZRTLDIR = ../../build-romhack
ACTORDIR = $(ZZRTLDIR)/actor/$(ACTORNUM)
OBJECTDIR = $(ZZRTLDIR)/object/$(OBJECTNUM)
UPDATETXT = $(ZZRTLDIR)/update.txt

.PHONY: copyactor copyobject default clean

.PRECIOUS: $(ACTORNAME).zovl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
%.elf: %.o
	$(LD) $(LDFLAGS) -T $(Z64OVLDIR)/z64ovl.ld -o $@ $< 
	
%.zovl: %.elf
	$(NOVL) -c -A $(BASEADDR) -o $@ $<
	
%.yaz0: %.zovl
	$(YAZ0) $< > $@
	
copyactor: $(ACTORNAME).zovl conf.txt
	rm -f $(ACTORDIR)/actor.zovl
	cp $^ $(ACTORDIR)/
	touch $(UPDATETXT)

copyobject: zobj.zobj
	cp zobj.zobj $(OBJECTDIR)/
	touch $(UPDATETXT)
	
clean:
	rm -fv $(ACTORNAME).o $(ACTORNAME).elf $(ACTORNAME).zovl *.i *.s *.map

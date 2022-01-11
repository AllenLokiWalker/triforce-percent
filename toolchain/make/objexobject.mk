zobj.zobj $(OBJECTNAME).h $(OBJECTNAME).ld: $(OBJECTNAME).objex $(OBJEXSUBFILES)
	$(ZZCONVERT) --in $(OBJECTNAME).objex --out zobj.zobj $(OBJEXSETTINGS) --header $(OBJECTNAME).h --linker $(OBJECTNAME).ld

.PHONY: objexclean

clean: objexclean

objexclean:
	rm -f zobj.zobj $(OBJECTNAME).h $(OBJECTNAME).ld

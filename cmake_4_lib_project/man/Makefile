none:

% : %.ronn
	ronn -r --pipe $< > $@
	sed -i '/^\.TH /s/ ""$$//' $@

cleanall:
	rm *[1-8]

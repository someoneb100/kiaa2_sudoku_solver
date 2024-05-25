TEX=pdflatex
BIB=bibtex
RESULT=dancing_links_petar_djordjevic

$(RESULT).pdf : $(RESULT).tex
	$(TEX) $^
	$(BIB) $(RESULT).aux
	$(TEX) $^
	$(TEX) $^

.PHONY: clean

clean:
	rm -rf *.aux *.bbl *.blg *.log *.out *.toc *.pdf
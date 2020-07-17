RM=rm -f
LATEX=latexmk -synctex=1 -interaction=nonstopmode --shell-escape -pdf

all: tests/test1/AEDA-T1-teor.pdf tests/test2/AEDA-T2-teor.pdf tests/test3/AEDA-T3-teor.pdf

FORCE:

%.pdf: %.tex
ifeq ($(VERSION),)
	cd $(<D) && $(LATEX) $(<F)
else
	cd $(<D) && (echo "$(VERSION)" > VERSION) && $(LATEX) $(<F) && $(RM) VERSION
endif

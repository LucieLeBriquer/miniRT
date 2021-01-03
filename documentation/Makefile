.PHONY:
	folders,clean,all

all: tex/*.tex schemas/*.tex images/*.png | folders
	@cd tex;\
	cp ~/.templateTex/pack.tex .;\
	pdflatex --output-directory=aux documentation.tex;\
	pdflatex --output-directory=aux documentation.tex;\
	mv aux/*.pdf ..;\
	rm pack.tex

folders:
	@mkdir -p tex/aux
	@mkdir -p pdf

clean:
	@rm -rf tex/aux pdf

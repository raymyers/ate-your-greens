build: build-haskell

test: test-haskell
    echo "Seems to work!"

build-haskell: bnfc
    cd generated/haskell && make

bnfc:
    bnfc -d -m grammar/Eyg.cf -o generated/haskell/

test-haskell:
    ./generated/haskell/Eyg/Test examples/example-all.eyg 

latex:
    bnfc --latex -m grammar/Eyg.cf -o doc/syntax/

doc: latex
    pdflatex doc/syntax/Eyg.tex

build-all: build-haskell doc

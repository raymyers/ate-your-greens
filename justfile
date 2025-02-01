build: build-haskell

test: test-haskell
    echo "Seems to work!"

build-haskell: bnfc-haskell
    cd generated/haskell && make

bnfc-haskell:
    bnfc -d -m grammar/Eyg.cf --haskell -o generated/haskell/

bnfc-c:
    bnfc -m grammar/Eyg.cf --c -o generated/c/

build-c: bnfc-c
    cd generated/c && make


test-haskell:
    ./generated/haskell/Eyg/Test examples/example-all.eyg 

test-c:
    ./generated/c/TestEyg examples/example-all.eyg 

latex:
    bnfc --latex -m grammar/Eyg.cf -o doc/syntax/

doc: latex
    cd doc/syntax && make

build-all: build-haskell doc

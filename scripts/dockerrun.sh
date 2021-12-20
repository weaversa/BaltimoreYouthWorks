#!/bin/bash

DIRYOUTH=$(realpath $1)
DIRWORK=$(realpath $2)

docker run --rm -it \
       --mount type=bind,src=$DIRYOUTH,dst=$DIRYOUTH \
       --mount type=bind,src=$DIRWORK,dst=$DIRWORK \
       --mount type=bind,src=$(pwd),dst=/output \
       --workdir=$(pwd) weaversa/youthworks $1 $2

echo "If successful, results were written to the file \`YouthworksMatching.xlsx\` in the current directory."

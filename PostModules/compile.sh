#compile all the basilisks post-processing modules
qcc -O2 -Wall getFacet.c -o getFacet -lm
qcc -O2 -Wall getData.c -o getData -lm
qcc -O2 -Wall getDeformation.c -o getDeformation -lm
qcc -O2 -Wall getTotalDeformation.c -o getTotalDeformation -lm
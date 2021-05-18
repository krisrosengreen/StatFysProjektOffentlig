cd SIAD_model
echo "starting"
echo "Kører SIAD.c"
gcc -o SIAD SIAD.c -L/path/to/libs -lm
./SIAD
echo "SIAD.c kørt"
gnuplot GNU_SIAD_PIC.p
echo "GNU_SIAD_PIC.p kørt"
gnuplot GNU_SIAD_PLOT.p
echo "GNU_SIAD_PLOT.p kørt"
gnuplot GNU_SIAD_CONSTANTS_PLOT.p
echo "GNU_SIAD_CONSTANTS_PLOT.p kørt"
cd ..
echo "færdig"

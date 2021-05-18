set terminal png size 2000,750
set output 'VISUAL_SIAD_CONSTANTS_PLOT.png'
set xrange [0:100]
set grid
plot 'DATA_CONSTANTS_PLOT_SIAD.txt' using 1:2 with linespoints lt 2 title 'R_0','DATA_CONSTANTS_PLOT_SIAD.txt' using 1:3 with linespoints lt 7 title 'beta','DATA_CONSTANTS_PLOT_SIAD.txt' using 1:4 with linespoints lt 22 title 'gamma'
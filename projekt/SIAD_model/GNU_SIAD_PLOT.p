set terminal png size 2000,750
set output 'VISUAL_SIAD_PLOT.png'
set xrange [0:100]
set yrange [-1:101]
set grid
plot 'DATA_PLOT_SIAD.txt' using 1:2 with linespoints lt 2 title 'raske','DATA_PLOT_SIAD.txt' using 1:3 with linespoints lt 7 title 'inficerede','DATA_PLOT_SIAD.txt' using 1:4 with linespoints lt 22 title 'Asymptomatiske','DATA_PLOT_SIAD.txt' using 1:5 with linespoints lt 17 title 'døde'
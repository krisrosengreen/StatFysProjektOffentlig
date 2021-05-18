set terminal png size 1000,1000
set output 'VISUAL_SIAD_data.png'
set xrange [-2:12]
set yrange [-2:12]
set grid
plot for [i=1:300.000000:3]'DATA_PARTIKEL_SIAD.txt' using i:i+1:i+2 with linespoints lc variable notitle
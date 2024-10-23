set terminal png size 800,600
set output 'sortup.png'

set title "Sorting Algorithm Performance"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale y;
set key top left

set key left top
set style data linespoints

plot 'resdown.txt' using 1:2 title 'BubbleSort' lw 2 lc rgb 'red', \
     'resdown.txt' using 1:3 title 'QuickSort' lw 2 lc rgb 'blue'

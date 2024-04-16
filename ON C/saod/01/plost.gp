#!/usr/bin/gnuplot

set termoption enhanced
set terminal svg size 1920, 1080 font "Arial, 16"
set output "image.svg"

set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 2 lc rgb "0x2A8D9C" lt 1 lw 4 pt 11 ps 1

set border lw 2
set grid
set key top left

set logscale y

set xlabel "Количество элементов в массиве"
set ylabel "Время выполнения, с" rotate by 90
set xtics 100000
set mxtics
set format x "%6.0f"
set format y "%.2f"

plot "res" using 1:2 title "Bubble Sort" with linespoints ls 1, \
"res" using 1:3 title "Counting Sort" with linespoints ls 2, \
"res" using 1:4 title "Merge Sort" with linespoints ls 3,



# "Скорость Bubble Sort зависит от размера входных данных и от их упорядоченности"
# "Скорость Counting Sort зависит от размера входных данных"
# "Скорость Merge Sort зависит от размера входных данных и немного от их упорядоченности" 
set terminal pngcairo enhanced font 'Verdana,12'
set terminal png size 1080, 500
set output 'time.png'
set title "Сравнение времени выполнения и коллизий для двух хеш-таблиц"
set xlabel "Количество элементов"
set ylabel "Время выполнения (сек)"
set logscale y;
set key top left

plot 'hashdate.txt' using 1:2 with lines lw 2 title "KR time", \
     'hashdate.txt' using 1:4 with lines lw 2 title "DJB time"
set terminal pngcairo enhanced font 'Verdana,12'
set terminal png size 1080, 500
set output 'collisions.png'
set title "Сравнение коллизий для двух хеш-таблиц"
set xlabel "Количество элементов"
set ylabel "Время выполнения (сек)"
set logscale y;
set key top left

plot 'res.txt' using 1:3 with lines lw 2 title "KR collisions", \
     'res.txt' using 1:5 with lines lw 2 title "ADD collisions"

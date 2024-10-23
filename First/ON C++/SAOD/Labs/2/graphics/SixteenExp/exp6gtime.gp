set terminal pngcairo enhanced font 'Verdana,12'
set terminal png size 1080, 500
set output 'time.png'
set title "Сравнение времени выполнения для двух хеш-таблиц"
set xlabel "Количество элементов"
set ylabel "Время выполнения (сек)"
set key top left

plot 'res.txt' using 1:2 with lines lw 2 title "KR time", \
     'res.txt' using 1:4 with lines lw 2 title "ADD time"
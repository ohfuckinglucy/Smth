set terminal pngcairo enhanced font 'Verdana,12'
set terminal png size 1080, 500
set output 'plot.png'
set title "Сравнение времени выполнения для дерева и хэш-таблицы"
set xlabel "Количество элементов"
set ylabel "Время выполнения (сек)"
set key top left

plot 'treedate1.txt' using 1:2 with lines lw 2 title "Дерево", \
     'hashdate1.txt' using 1:2 with lines lw 2 title "Хэш таблица"

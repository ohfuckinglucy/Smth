set style line 1 lc rgb "purple" lt 1 lw 2 pt 7 ps 1.5 # Фиолетовая линия, квадратные маркеры
set style line 2 lc rgb "red" lt 1 lw 2 pt 5 ps 1.5    # Красная линия, треугольные маркеры
set style line 3 lc rgb "green" lt 1 lw 2 pt 9 ps 1.5 # Зелёная линия, круглые маркеры

set terminal pngcairo enhanced font 'Verdana,12'
set terminal png size 1080, 500
set output "plot.png"             # Указываем имя файла для сохранения графика
set logscale x
set xlabel "Размер массива"
set ylabel "Время выполнения (сек)"
set key top left

plot "res.txt" using 1:4 title "Bubble Sort" with linespoints ls 1, \
     "" using 1:2 title "Heap Sort" with linespoints ls 2, \
     "" using 1:3 title "Counting Sort" with linespoints ls 3

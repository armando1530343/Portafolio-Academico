Arc=IGC_PRACTICA05_DOMINGUEZ_DE_LA_CRUZ_MAGALY_ALEJANDRA

rm $Arc
g++ -g3 *.cpp -o $Arc -I/usr/X11R/include -L/usr/X11R/lib -lglut -lGL -lGLU -lm  
./$Arc

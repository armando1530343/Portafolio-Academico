Arc=proyecto2

rm $Arc
g++ -g3 *.cpp -o $Arc -I/usr/X11R/include -L/usr/X11R/lib -lglut -lGL -lGLU -lm  
./$Arc


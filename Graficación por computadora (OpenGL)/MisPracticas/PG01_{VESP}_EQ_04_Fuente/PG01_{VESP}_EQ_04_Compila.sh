#Arc=main
Arc=PG01_{VESP}_EQ_04_Servidor


rm $Arc
g++ -g3 $Arc.cpp -o $Arc -I/usr/X11R/include -L/usr/X11R/lib -lglut -lGL -lGLU -lm
#g++ -g3 $Arc.c -o $Arc -I/usr/X11R/include -L/usr/X11R/lib -lXi -lXmu -lglut -lGL -lGLU -lm  
./$Arc

#!/bin/bash
#Carpeta=02_HemisferioRustico
Archivo=stan

#cd $Carpeta
rm $Archivo
g++ *.cpp -o $Archivo -lGL -lglut -lGLU -lGLEW -lm
./$Archivo
cd ..

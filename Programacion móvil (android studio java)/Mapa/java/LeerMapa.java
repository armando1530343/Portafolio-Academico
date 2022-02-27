package com.example.armando.mapa;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

public class LeerMapa extends AppCompatActivity{

    ArrayList<Ciudad> ciudades;
    String [] archivos;
    String file;
    ConstruirMapa c;

    public LeerMapa(String file, String [] archivos, ConstruirMapa c){
        this.file = file;
        this.archivos = archivos;
        this.c = c;
    }

    public void lectura(){
        ciudades = new ArrayList<Ciudad>();

        if(existe(archivos, file)){
            /*try{
                InputStreamReader archivo = new InputStreamReader(openFileInput(file));
                BufferedReader br = new BufferedReader(archivo);

                String linea = br.readLine();


                while(linea != null){

                    Ciudad c = new Ciudad();

                    String nombre = "";
                    String numero = "";
                    int comas = 0;
                    int cont = 0;
                    for(int i = 0; i < linea.length(); i++){
                        if(linea.charAt(i) != ','){
                            if(comas == 0){
                                nombre += linea.charAt(i);
                            }
                            else{
                                numero += linea.charAt(i);
                            }

                        }
                        else {

                            if(comas == 0){
                                c.setNombre(nombre);
                            }
                            else{

                                c.setDistancia(cont, Float.parseFloat(numero));
                                cont ++;
                            }
                            numero = "";
                            comas++;
                        }
                    }

                    ciudades.add(c);
                    Toast.makeText(this, linea, Toast.LENGTH_SHORT);

                    linea = br.readLine();
                }

                archivo.close();

            }
            catch(Exception e){

            }*/
        }
        else
            Toast.makeText(c, "No existe el archivo", Toast.LENGTH_SHORT);
    }

    public void nueva_ciudad(String ciudad){

        int num_ciudades = ciudades.size();


        try{
            OutputStreamWriter archivo = new OutputStreamWriter(openFileOutput(file, Activity.MODE_PRIVATE));
            String dist;
            for(int i = 0; i < ciudades.size(); i++){
                dist = "";
                for(int j = 0; j < ciudades.get(i).getDistancias().size(); j++){
                    dist += ("," + ciudades.get(i).getDistancias().get(j));
                }
                archivo.write(ciudades.get(i).getNombre() + dist);
            }

            dist = "";
            for(int i = 0; i < num_ciudades; i++){
                dist += ",0";
            }
            archivo.write(ciudad + dist);
            archivo.flush();
            archivo.close();

        }
        catch(Exception e){

        }

        lectura();
    }

    public ArrayList<Ciudad> getCiudades(){
        return ciudades;
    }

    public boolean existe(String [] arch, String filename){
        for(int i = 0; i < arch.length; i++){
            if(arch[i].equals(filename))
                return true;
        }

        return false;
    }


}

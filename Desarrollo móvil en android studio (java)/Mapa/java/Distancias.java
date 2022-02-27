package com.example.armando.mapa;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TableLayout;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Distancias extends AppCompatActivity {

    ListView distancias;

    String [] archivos;

    String file = "mapa.txt";

    ArrayList<String> distancias_ciudades = new ArrayList<String>();



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_distancias);

        distancias = (ListView)findViewById(R.id.distancias);

        archivos = fileList();

        lectura();

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.list_distancias, distancias_ciudades);
        distancias.setAdapter(adapter);



    }

    public void lectura(){

        if(existe(archivos, file)){
            try{
                InputStreamReader archivo = new InputStreamReader(openFileInput(file));
                BufferedReader br = new BufferedReader(archivo);

                String linea = br.readLine();


                while(linea != null){

                    distancias_ciudades.add(linea);
                    linea = br.readLine();
                }

                archivo.close();

            }
            catch(Exception e){

            }


        }
        else
            Toast.makeText(this, "No existe el archivo", Toast.LENGTH_SHORT).show();
    }
    public boolean existe(String [] arch, String filename){
        for(int i = 0; i < arch.length; i++){

            if(arch[i].equals(filename)) {

                return true;
            }
        }



        return false;
    }
}

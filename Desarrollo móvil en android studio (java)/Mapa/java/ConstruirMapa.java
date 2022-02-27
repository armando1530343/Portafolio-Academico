package com.example.armando.mapa;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.lang.reflect.Array;
import java.util.ArrayList;

public class ConstruirMapa extends AppCompatActivity {

    //LeerMapa mapa;

    EditText ciudad_txt, distancia_txt;

    String [] archivos;

    ArrayList<Ciudad> ciudades;

    ArrayList<String> nombre_ciudad;

    Spinner origen_sp, destino_sp;

    String file = "mapa.txt";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_construir_mapa);

        archivos = fileList();
        ciudad_txt = (EditText)findViewById(R.id.ciudad_txt);
        distancia_txt = (EditText)findViewById(R.id.distancia_txt);


        origen_sp = (Spinner)findViewById(R.id.origen_sp);
        destino_sp = (Spinner)findViewById(R.id.destino_sp);

        lectura();



    }

    public void lectura(){
        ciudades = new ArrayList<Ciudad>();
        nombre_ciudad = new ArrayList<String>();

        if(existe(archivos, file)){
            try{
                InputStreamReader archivo = new InputStreamReader(openFileInput(file));
                BufferedReader br = new BufferedReader(archivo);

                String linea = br.readLine();


                while(linea != null){

                    Ciudad c = new Ciudad();

                    //Toast.makeText(this, "Ciudad: " + linea, Toast.LENGTH_SHORT).show();

                    String nombre = "";
                    String numero = "";
                    int comas = 0;
                    int cont = 0;
                    for(int i = 0; i < linea.length(); i++){
                        //Toast.makeText(this, "char: " + linea.charAt(i), Toast.LENGTH_SHORT).show();
                        if(linea.charAt(i) != ','){
                            if(comas == 0){
                                nombre += linea.charAt(i);
                            }
                            else{
                                numero += linea.charAt(i);
                            }

                        }
                        else {
                            //Toast.makeText(this, "char: " + linea.charAt(i), Toast.LENGTH_SHORT).show();
                            if(comas == 0){
                                c.setNombre(nombre);
                            }
                            else{
                                //Toast.makeText(this,  nombre + " " + cont + ":" + numero, Toast.LENGTH_SHORT).show();

                                c.addDistancia(cont, Integer.parseInt(numero));
                                cont ++;
                            }
                            numero = "";
                            comas++;
                        }

                        if(i == linea.length()-1){
                            c.addDistancia(cont, Integer.parseInt(numero));
                        }
                    }

                    ciudades.add(c);

                    linea = br.readLine();
                }

                archivo.close();

            }
            catch(Exception e){

            }

            for(int i = 0; i < ciudades.size(); i++){
                nombre_ciudad.add(ciudades.get(i).getNombre());
            }

            ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, nombre_ciudad);

            origen_sp.setAdapter(adapter);
            destino_sp.setAdapter(adapter);


        }
        else
            Toast.makeText(this, "No existe el archivo", Toast.LENGTH_SHORT).show();
    }

    public void nueva_ciudad(View v){

        int num_ciudades = ciudades.size();
        //Toast.makeText(this, "num: " +  num_ciudades, Toast.LENGTH_SHORT).show();


        try{
            OutputStreamWriter archivo = new OutputStreamWriter(openFileOutput(file, Activity.MODE_PRIVATE));
            String dist;
            for(int i = 0; i < num_ciudades; i++){
                dist = "";
                /*Toast.makeText(this,
                        "ciudad: " +  ciudades.get(i).getNombre() +
                        " - dist: " +  ciudades.get(i).getDistancias().size(), Toast.LENGTH_SHORT).show();*/
                for(int j = 0; j < ciudades.get(i).getDistancias().size(); j++){
                    dist += ("," + ciudades.get(i).getDistancias().get(j));
                }
                /*for(int j = ciudades.get(i).getDistancias().size(); j < num_ciudades; j++){
                    dist += ("," + ciudades.get(i).getDistancias().get(j));
                }*/
                dist += ",0";
                archivo.write(ciudades.get(i).getNombre() + dist + "\n");
            }

            dist = "";
            for(int i = 0; i < num_ciudades+1; i++){
                dist += ",0";
            }
            archivo.write(ciudad_txt.getText().toString() + dist + "\n");
            archivo.flush();
            archivo.close();

            //Toast.makeText(this, "agregado: " +  ciudad_txt.getText().toString() + dist, Toast.LENGTH_SHORT).show();

        }
        catch(Exception e){

        }

        lectura();

        ciudad_txt.setText("");

    }

    public void crear_camino(View v){
        Toast.makeText(this,origen_sp.getSelectedItem().toString(), Toast.LENGTH_SHORT ).show();

        int index_origen = 0, index_destino = 0;

        for(int i = 0; i < ciudades.size(); i++){
            if(ciudades.get(i).getNombre().equals(origen_sp.getSelectedItem().toString()))
                index_origen = i;
            if(ciudades.get(i).getNombre().equals(destino_sp.getSelectedItem().toString()))
                index_destino = i;
        }

        ciudades.get(index_origen).setDistancia(index_destino, Integer.parseInt(distancia_txt.getText().toString()));
        ciudades.get(index_destino).setDistancia(index_origen, Integer.parseInt(distancia_txt.getText().toString()));

        if(origen_sp.getSelectedItem().toString().equals(destino_sp.getSelectedItem().toString())){
            ciudades.get(index_origen).setDistancia(index_destino, 0);
            ciudades.get(index_destino).setDistancia(index_origen, 0);
        }



        try{
            OutputStreamWriter archivo = new OutputStreamWriter(openFileOutput(file, Activity.MODE_PRIVATE));

            for(int i = 0; i < ciudades.size(); i++){
                String dist = "";

                for(int j = 0; j < ciudades.get(i).getDistancias().size(); j++){
                    dist += ("," + ciudades.get(i).getDistancias().get(j));
                }
                archivo.write(ciudades.get(i).getNombre() + dist + "\n");
            }

            archivo.flush();
            archivo.close();

        }
        catch(Exception e){

        }

        lectura();

        distancia_txt.setText("");
    }

    public void borrar_mapa(View v){
        try{
            OutputStreamWriter archivo = new OutputStreamWriter(openFileOutput(file, Activity.MODE_PRIVATE));
            archivo.write("");
            archivo.flush();
            archivo.close();

            Toast.makeText(this, "Mapa borrado", Toast.LENGTH_SHORT).show();

        }
        catch(Exception e){

        }
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

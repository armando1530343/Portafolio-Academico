package com.example.armando.mapa;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Ruta extends AppCompatActivity {

    String [] archivos;

    ArrayList<Ciudad> ciudades;

    String file = "mapa.txt";

    ArrayList<String> nombre_ciudad;

    Spinner origen_sp, destino_sp;

    ArrayList<Integer> indices_recorridos = new ArrayList<Integer>();

    int distancia_total = 0;

    String ruta = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ruta);

        origen_sp = (Spinner)findViewById(R.id.origen_sp);
        destino_sp = (Spinner)findViewById(R.id.destino_sp);
        archivos = fileList();

        lectura();
    }

    public void ruta(View v){

        String origen = origen_sp.getSelectedItem().toString();
        String destino = destino_sp.getSelectedItem().toString();

        int index_origen = 0;
        int index_destino = 0;

        for(int i = 0; i < ciudades.size(); i++){
            if(ciudades.get(i).getNombre().equals(origen))
                index_origen = i;

            if(ciudades.get(i).getNombre().equals(destino))
                index_destino = i;
        }

        int nodos_recorridos = 0;

        menor_distancia(index_origen, index_destino);
        ruta += ciudades.get(index_destino).getNombre();

        //Toast.makeText(this, ruta, Toast.LENGTH_SHORT).show();

        TextView ruta_txt = (TextView)findViewById(R.id.ruta_txt);
        ruta_txt.setText("Ruta: " + ruta);

        TextView distancia_txt = (TextView)findViewById(R.id.distancia_txt);
        distancia_txt.setText("Distancia Total: " + distancia_total);

        ruta = "";
        distancia_total = 0;
        indices_recorridos.clear();

    }

    private void menor_distancia(int index, int index2){

        indices_recorridos.add(index);

        int menor = 100000;
        int ind = -1;
        for(int i = 0; i < ciudades.size(); i++){

            boolean romper = false;
            for(int j = 0; j < indices_recorridos.size(); j++){
                if(i == indices_recorridos.get(j)){
                    romper = true;
                    break;
                }
            }

            if(romper)
                continue;

            int dist = ciudades.get(index).getDistancias().get(i);
            if(dist != 0) {
                if(ciudades.get(index).getDistancias().get(index2) != 0){
                    menor = ciudades.get(index).getDistancias().get(index2);
                    ind = index2;
                }
                else if(dist < menor){
                    menor = dist;
                    ind = i;
                }
            }
        }

        distancia_total += menor;
        ruta += (ciudades.get(index).getNombre() + ",");

        if(ind != -1 && ind != index2)
            menor_distancia(ind, index2);
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
    public boolean existe(String [] arch, String filename){
        for(int i = 0; i < arch.length; i++){

            if(arch[i].equals(filename)) {

                return true;
            }
        }



        return false;
    }
}

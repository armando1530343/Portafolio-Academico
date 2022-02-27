package com.example.armando.timer555calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

import java.util.ArrayList;

public class Valores extends AppCompatActivity {

    ListView lista;
    EditText tiempo_txt;

    float [][] datos = {
            {1.0f, 910000, 0} ,
            {10.0f, 91000, 0},
            {11.0f, 82000, 0},
            {12.1f, 75000, 0},
            {13.3f, 68000, 0}
    };

    ArrayList<String> info;

    float tiempo_pulso = 1.0f;
    float s = 1000000000f, ms, us, ns, ps;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_valores);

        lista = (ListView)findViewById(R.id.list);
        tiempo_txt = (EditText)findViewById(R.id.tiempo_txt);

        info = new ArrayList<String>();

        ms = s/1000;
        us = ms/1000;
        ns = us/1000;
        ps = ns/1000;

        calcular_datos();

    }

    public void calcular(View v){
        info.clear();
        tiempo_pulso = Float.parseFloat(tiempo_txt.getText().toString());
        calcular_datos();
    }
    public void calcular_datos(){

        info.add("R        C        Ancho Pulso");

        for(int i = 0; i < 5; i++) {
            datos[i][2] = tiempo_pulso * datos[i][0] * datos[i][1];

            float ancho = datos[i][2];
            float C = datos[i][1];

            //ancho =  tiempo_pulso * (R*C);

            String unidad = "", unidad2 = "";

            if(ancho > s) {ancho /= s; unidad = "s"; }
            else if(ancho > ms){ancho /= ms; unidad = "ms";}
            else if(ancho > us){ancho /= us; unidad = "us";}
            else if(ancho > ns){ancho /= ns; unidad = "ns";}
            else {ancho /= ps; unidad = "ns";}

            if(C > s) {C /= s; unidad2 = "s"; }
            else if(C > ms){C /= ms; unidad2 = "ms";}
            else if(C > us){C /= us; unidad2= "us";}
            else if(C > ns){C /= ns; unidad2 = "ns";}
            else {C /= ps; unidad2 = "ns";}

            info.add(String.format("%.1f Om     %.1f%s        %.1f%s",datos[i][0], C, unidad2, ancho, unidad));
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, info);
        lista.setAdapter(adapter);

    }
}

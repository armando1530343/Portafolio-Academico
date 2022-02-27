package com.example.armando.timer555calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

public class AnchoPulso extends AppCompatActivity {

    Spinner R_sp, C_sp;
    EditText R_txt, C_txt;
    TextView ancho_txt;

    float ancho_pulso;
    float tiempo_pulso = 1.1f;
    String unidad = "";

    float s = 1000000000f, ms, us, ns, ps;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ancho_pulso);

        R_sp = (Spinner)findViewById(R.id.R_sp);
        C_sp = (Spinner)findViewById(R.id.C_sp);

        R_txt = (EditText)findViewById(R.id.R_txt);
        C_txt = (EditText)findViewById(R.id.C_txt);

        ancho_txt = (TextView)findViewById(R.id.ancho_txt);

        String [] unidades_R = {"O","kO", "MO"};
        String [] unidades_C = {"µF","nF", "pF"};

        ms = s/1000;
        us = ms/1000;
        ns = us/1000;
        ps = ns/1000;


        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, unidades_R);
        R_sp.setAdapter(adapter);

        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, unidades_C);
        C_sp.setAdapter(adapter);
    }

    public void calcular(View v){
        if(R_txt.getText().length() > 0 && C_txt.getText().length() > 0){
            float R = Float.parseFloat(R_txt.getText().toString());
            float C = Float.parseFloat(C_txt.getText().toString());

            String unidad_R = R_sp.getSelectedItem().toString();
            String unidad_C = C_sp.getSelectedItem().toString();

            float unidad1 = unidad_R == "O" ? 1 : unidad_R == "kO" ? 1000 : 1000000;
            float unidad2 = unidad_C == "µF" ? us : unidad_C == "nF" ? ns : ps;

            R *= unidad1;
            C *= unidad2;

            /*

            T*R*C = A

            1000000000   = 1s
            1000000      = 1ms
            1000         = 1us
            1            = 1ns
            0.001               = 1ps

            */

            //int x = 1000000000;

            float ancho =  tiempo_pulso * (R*C);

            if(ancho > s) {ancho /= s; unidad = "s"; }
            else if(ancho > ms){ancho /= ms; unidad = "ms";}
            else if(ancho > us){ancho /= us; unidad = "us";}
            else if(ancho > ns){ancho /= ns; unidad = "ns";}
            else {ancho /= ps; unidad = "ns";}


            ancho_txt.setText(String.format("%.3f %s", ancho, unidad));
            //
        }
        else
            Toast.makeText(this, "Hay campos vacios", Toast.LENGTH_SHORT).show();



    }
}

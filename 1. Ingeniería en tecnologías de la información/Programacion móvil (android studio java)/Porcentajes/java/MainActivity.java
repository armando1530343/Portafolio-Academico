package com.example.armando.porcentajes;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void opcion1(View v){
        Intent opc1 = new Intent(this, PorcentajeSimple.class);
        startActivity(opc1);
    }

    public void opcion2(View v){
        Intent opc2 = new Intent(this, Propina.class);
        startActivity(opc2);
    }

    public void opcion3(View v){
        Intent opc3 = new Intent(this, Descuento.class);
        startActivity(opc3);
    }
    public void opcion4(View v){
        Intent opc4 = new Intent(this, Fracciones.class);
        startActivity(opc4);
    }
}

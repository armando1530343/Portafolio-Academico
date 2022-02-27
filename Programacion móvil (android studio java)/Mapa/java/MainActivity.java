package com.example.armando.mapa;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Layout;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void page1 (View v){
        Intent page = new Intent(this, ConstruirMapa.class);
        startActivity(page);
    }

    public void page2 (View v){
        Intent page = new Intent(this, Ruta.class);
        startActivity(page);
    }

    public void page3 (View v){
        Intent page = new Intent(this, Distancias.class);
        startActivity(page);
    }
}

package com.example.armando.timer555calculator;

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
    public void pagina1(View v){
        Intent p = new Intent(this, AnchoPulso.class);
        startActivity(p);
    }
    public void pagina2(View v){
        Intent p = new Intent(this, Valores.class);
        startActivity(p);
    }
}

package com.example.victoria.club_nautico;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    Button bt1, bt2, bt3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt1 = (Button)findViewById(R.id.persona);
        bt2 = (Button)findViewById(R.id.barco);
        bt3 = (Button)findViewById(R.id.salidas);

        bt1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, Persona.class);
                startActivity(intent);
            }
        });
        bt2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, Barco.class);
                startActivity(intent);
            }
        });
        bt3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, Salidas.class);
                startActivity(intent);
            }
        });
    }
}

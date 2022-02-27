package com.example.armando.porcentajes;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class Fracciones extends AppCompatActivity {

    EditText numA, numB, numC;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fracciones);
    }

    public void calcular(View v){
        numA = (EditText)findViewById(R.id.numA);
        numB = (EditText)findViewById(R.id.numB);
        numC = (EditText)findViewById(R.id.numC);

        float a, b, c;

        if(numA.getText().length() > 0 && numB.getText().length() > 0){
            a = Float.parseFloat(numA.getText().toString());
            b = Float.parseFloat(numB.getText().toString());

            c = a/(b/100);
            numC.setText("" + c);
        }
        else if(numA.getText().length() > 0 && numC.getText().length() > 0){
            a = Float.parseFloat(numA.getText().toString());
            c = Float.parseFloat(numC.getText().toString());
            b = (a/c)*100;
            numB.setText("" + b);
        }
        else if(numB.getText().length() > 0 && numC.getText().length() > 0){
            b = Float.parseFloat(numB.getText().toString());
            c = Float.parseFloat(numC.getText().toString());

            a = c * (b/100);
            numA.setText("" + a);
        }
    }
}

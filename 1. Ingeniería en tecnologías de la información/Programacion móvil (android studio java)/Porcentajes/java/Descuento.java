package com.example.armando.porcentajes;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class Descuento extends AppCompatActivity {

    EditText numA, numB, numC, numD;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_descuento);
    }

    public void calcular(View v) {

        numA = (EditText) findViewById(R.id.numA);
        numB = (EditText) findViewById(R.id.numB);
        numC = (EditText) findViewById(R.id.numC);
        numD = (EditText) findViewById(R.id.numD);

        float a, b, c, d;

        if (numA.getText().length() > 0 && numB.getText().length() > 0) {
            a = Float.parseFloat(numA.getText().toString());
            b = Float.parseFloat(numB.getText().toString());
            c = a - (a/100)*b;
            d = a - c;
            numC.setText("" + c);
            numD.setText("" + d);
        } else if (numA.getText().length() > 0 && numC.getText().length() > 0) {
            a = Float.parseFloat(numA.getText().toString());
            c = Float.parseFloat(numC.getText().toString());
            b = (a-c) / (a/100);
            d = a - c;
            numB.setText("" + b);
            numD.setText("" + d);

        } else if (numA.getText().length() > 0 && numD.getText().length() > 0) {
            a = Float.parseFloat(numA.getText().toString());
            d = Float.parseFloat(numD.getText().toString());
            c = a - d;
            b = (a-c) / (a/100);
            numB.setText("" + b);
            numC.setText("" + c);
        } else if (numB.getText().length() > 0 && numC.getText().length() > 0) {
            b = Float.parseFloat(numB.getText().toString());
            c = Float.parseFloat(numC.getText().toString());

            a = c / (100 - b) * 100;
            d = a - c;
            numA.setText("" + a);
            numD.setText("" + d);
        } else if (numC.getText().length() > 0 && numD.getText().length() > 0) {
            c = Float.parseFloat(numC.getText().toString());
            d = Float.parseFloat(numD.getText().toString());
            a = c + d;
            b = (a-c) / (a/100);
            numA.setText("" + a);
            numB.setText("" + b);
        }
    }
}

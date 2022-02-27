package com.example.armando.porcentajes;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class PorcentajeSimple extends AppCompatActivity {

    int i = 0;
    EditText numA, numB, numC;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_porcentaje_simple);

        numA = (EditText)findViewById(R.id.numA);
        numB = (EditText)findViewById(R.id.numB);
        numC = (EditText)findViewById(R.id.numC);
    }



    public void calcular(View v){
        float a;// = Float.parseFloat(numA.getText().toString());
        float b;// = Float.parseFloat(numB.getText().toString());
        float c;// = Float.parseFloat(numC.getText().toString());

        //c = (b/100)*a
        //a = c / (b/100)
        //b = (c/a)*100

        if(numA.getText().length() > 0 && numB.getText().length() > 0) {
            a = Float.parseFloat(numA.getText().toString());
            b = Float.parseFloat(numB.getText().toString());
            numC.setText("" + (b / 100) * a);
        }

        else if(numA.getText().length() == 0 && numB.getText().length() > 0 && numC.getText().length() > 0) {
            b = Float.parseFloat(numB.getText().toString());
            c = Float.parseFloat(numC.getText().toString());
            numA.setText("" + c / (b / 100));
        }

        else if(numA.getText().length() > 0 && numB.getText().length() == 0 && numC.getText().length() > 0) {
            a = Float.parseFloat(numA.getText().toString());
            c = Float.parseFloat(numC.getText().toString());
            numB.setText("" + (c / a) * 100);
        }
    }
}

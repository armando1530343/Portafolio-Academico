package com.example.victoria.club_nautico;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.Toast;

import java.util.ArrayList;

public class Barco extends AppCompatActivity {

    String nombre_bd = "club.db";

    Button btn1, btn2, btn3, btn4;
    EditText num, cuota;
    Spinner propietario;
    ListView barcos;

    String tabla = "Barco";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    AgendaSqlite sqlite;
    SQLiteDatabase database;
    Cursor cursor;
    ArrayList<String> list_barcos = new ArrayList<String>();
    ArrayList<String> propietarios = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_barco);
        btn1 = (Button)findViewById(R.id.btn1);
        btn2 = (Button)findViewById(R.id.btn2);
        btn3 = (Button)findViewById(R.id.btn3);
        btn4 = (Button)findViewById(R.id.btn4);

        num = (EditText)findViewById(R.id.num);
        cuota = (EditText)findViewById(R.id.cuota);
        propietario = (Spinner)findViewById(R.id.propietario);
        barcos = (ListView)findViewById(R.id.barcos);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        sqlite = new AgendaSqlite(this, nombre_bd, null, 1 );

        getPersonas();

        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Barco.this,
                android.R.layout.simple_spinner_item, propietarios);
        propietario.setAdapter(adapter2);

        RegistrosBarcos();

        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(num.getText().length() > 0 && cuota.getText().length() > 0 && propietario.getCount() > 0){

                    if(sqlite.getWritableDatabase() != null){
                        //database.close();
                        if(!validar(num.getText().toString())){
                            try {
                                ContentValues values = new ContentValues();
                                values.put("num", num.getText().toString());
                                values.put("cuota", cuota.getText().toString());
                                values.put("propietario", propietario.getSelectedItem().toString());

                                Toast.makeText(Barco.this, propietario.getSelectedItem().toString(), Toast.LENGTH_LONG ).show();

                                database = sqlite.getWritableDatabase();
                                database.insert(tabla, null, values);
                                database.close();
                                RegistrosBarcos();
                                AD.setMessage("Se añadió correctamente");
                                AD.show();

                                num.setText("");
                                cuota.setText("");
                            }
                            catch (Exception e){
                                AD.setMessage(e.getMessage());
                                AD.show();
                            }

                        }
                        else{
                            AD.setMessage("Ya existe la No.Amarre");
                            AD.show();
                        }
                    }

                }
            }
        });
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                cuota.setText("");
                if(num.getText().length() > 0){
                    if(sqlite.getReadableDatabase() != null){

                        database = sqlite.getReadableDatabase();
                        cursor = database.rawQuery("select * from " + tabla +
                                " where num = " + num.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            cuota.setText(cursor.getString(1));

                            int n = propietarios.size()+1;
                            String [] per = new String[n];
                            per[0] = cursor.getString(2);
                            for(int i = 0; i < n-1; i++)
                                per[i+1] = propietarios.get(i);
                            ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Barco.this,
                                    android.R.layout.simple_spinner_item, per);
                            propietario.setAdapter(adapter2);
                        }
                        else{
                            AD.setMessage("No hay No.Amarre");
                            AD.show();
                        }
                        cursor.close();
                        database.close();
                    }

                }
                else{
                    AD.setMessage("Debes poner la No.Amarre");
                    AD.show();
                }
            }
        });
        btn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(num.getText().length() > 0 && cuota.getText().length() > 0 && propietario.getCount() > 0){
                    if(sqlite.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("num", num.getText().toString());
                        values.put("cuota", cuota.getText().toString());
                        values.put("propietario", propietario.getSelectedItem().toString());

                        database = sqlite.getWritableDatabase();
                        database.update(tabla, values,"num="+num.getText().toString(), null);
                        database.close();
                        RegistrosBarcos();
                        AD.setMessage("Se actualizo la tabla Barcos");
                        AD.show();

                        num.setText("");
                        cuota.setText("");
                    }

                }
            }
        });
        btn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(num.getText().length() > 0){
                    if(sqlite.getWritableDatabase() != null){

                        database = sqlite.getWritableDatabase();
                        String [] args = {num.getText().toString()};
                        database.execSQL("delete from Salidas where barco = ?", args);
                        database.execSQL("delete from Barco where num = ?", args);

                        database.close();
                        RegistrosBarcos();
                        AD.setMessage("Se borro el barco");
                        AD.show();
                        num.setText("");
                        cuota.setText("");

                    }
                }
                else{
                    AD.setMessage("Debes poner la No.Amarre");
                    AD.show();
                }

            }
        });
    }
    void getPersonas()
    {
        String matricula;
        String Fin="";
        database = sqlite.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from Persona", null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    matricula = cursor.getString(0);
                    propietarios.add(matricula);

                }
                while(cursor.moveToNext());
            }
            cursor.close();
        }

        database.close();
    }
    boolean validar (String num)
    {
        String Fin="";
        SQLiteDatabase db = sqlite.getReadableDatabase();
        cursor = db.rawQuery("select * from " + tabla + " where num = " + num , null);

        if (cursor.getCount() > 0) {
            return true;
        }
        cursor.close();
        db.close();

        return false;
    }
    void RegistrosBarcos ()
    {
        list_barcos.clear();
        String num, cuota, propietario;
        String Fin="";
        database = sqlite.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    num = cursor.getString(0);
                    cuota = cursor.getString(1);
                    propietario = cursor.getString(2);
                    list_barcos.add(num + ", " + cuota + ", " + propietario + "\n");
                }
                while(cursor.moveToNext());

            }
            cursor.close();
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<>(Barco.this,
                android.R.layout.simple_list_item_1, list_barcos);
        barcos.setAdapter(adapter);

        database.close();
    }
}

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
import android.widget.TextView;
import android.view.View.OnClickListener;

import java.util.ArrayList;

public class Persona extends AppCompatActivity {
    String nombre_bd = "club.db";

    Button btn1, btn2, btn3, btn4;
    EditText matricula, nombre;
    Spinner relacion;
    ListView personas;

    String tabla = "Persona";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    AgendaSqlite sqlite;
    SQLiteDatabase database;
    Cursor cursor;
    ArrayList<String> list_personas = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_persona);

        btn1 = (Button)findViewById(R.id.btn1);
        btn2 = (Button)findViewById(R.id.btn2);
        btn3 = (Button)findViewById(R.id.btn3);
        btn4 = (Button)findViewById(R.id.btn4);

        matricula = (EditText)findViewById(R.id.matricula);
        nombre = (EditText)findViewById(R.id.nombre);
        relacion = (Spinner)findViewById(R.id.relacion);
        personas = (ListView)findViewById(R.id.personas);

        String [] rel = {"Socio", "No Socio"};
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, rel);
        relacion.setAdapter(adapter);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        sqlite = new AgendaSqlite(this, nombre_bd, null, 1 );

        RegistrosPersonas();

        btn1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                if(matricula.getText().length() > 0 && nombre.getText().length() > 0 && relacion.getCount() > 0){

                    if(sqlite.getWritableDatabase() != null){
                        //database.close();
                        if(!validar(matricula.getText().toString())){
                            ContentValues values = new ContentValues();
                            values.put("matricula", matricula.getText().toString());
                            values.put("nombre", nombre.getText().toString());
                            values.put("relacion", relacion.getSelectedItem().toString());

                            database = sqlite.getWritableDatabase();
                            database.insert(tabla, null, values);
                            database.close();
                            RegistrosPersonas();
                            AD.setMessage("Se añadió correctamente");
                            AD.show();

                            matricula.setText("");
                            nombre.setText("");

                        }
                        else{
                            AD.setMessage("Ya existe la matricula");
                            AD.show();
                        }
                    }

                }
            }
        });
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                nombre.setText("");
                if(matricula.getText().length() > 0){
                    if(sqlite.getReadableDatabase() != null){

                        database = sqlite.getReadableDatabase();
                        cursor = database.rawQuery("select * from " + tabla +
                                " where matricula = " + matricula.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            nombre.setText(cursor.getString(1));

                            String [] per = {cursor.getString(2), "Socio", "No Socio"};
                            ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Persona.this,
                                    android.R.layout.simple_spinner_item, per);
                            relacion.setAdapter(adapter2);
                        }
                        else{
                            AD.setMessage("No hay matricula");
                            AD.show();
                        }
                        cursor.close();
                        database.close();
                    }

                }
                else{
                    AD.setMessage("Debes poner la matricula");
                    AD.show();
                }
            }
        });
        btn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(matricula.getText().length() > 0 && nombre.getText().length() > 0 && relacion.getCount() > 0){
                    if(sqlite.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("matricula", matricula.getText().toString());
                        values.put("nombre", nombre.getText().toString());
                        values.put("relacion", relacion.getSelectedItem().toString());

                        database = sqlite.getWritableDatabase();
                        database.update(tabla, values,"matricula="+matricula.getText().toString(), null);
                        database.close();
                        RegistrosPersonas();
                        AD.setMessage("Se actualizo la tabla Personas");
                        AD.show();

                        matricula.setText("");
                        nombre.setText("");
                    }

                }
            }
        });
        btn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(matricula.getText().length() > 0){
                    if(sqlite.getWritableDatabase() != null){

                        database = sqlite.getWritableDatabase();
                        String [] args = {matricula.getText().toString()};
                        database.execSQL("delete from Barco where propietario = ?", args);
                        database.execSQL("delete from Salidas where patron = ?", args);
                        database.execSQL("delete from Persona where matricula = ?", args);
                        database.close();
                        RegistrosPersonas();
                        AD.setMessage("Se borro la Persona");
                        AD.show();
                        matricula.setText("");
                        nombre.setText("");

                    }
                }
                else{
                    AD.setMessage("Debes poner la matricula");
                    AD.show();
                }

            }
        });

    }
    boolean validar (String matricula)
    {
        String Fin="";
        SQLiteDatabase db = sqlite.getReadableDatabase();
        cursor = db.rawQuery("select * from " + tabla + " where matricula = " + matricula , null);

        if (cursor.getCount() > 0) {
            return true;
        }
        cursor.close();
        db.close();

        return false;
    }
    void RegistrosPersonas ()
    {
        list_personas.clear();
        String matricula, nombre, relacion;
        String Fin="";
        database = sqlite.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    matricula = cursor.getString(0);
                    nombre = cursor.getString(1);
                    relacion = cursor.getString(2);
                    list_personas.add(matricula + ", " + nombre + ", " + relacion + "\n");
                }
                while(cursor.moveToNext());

            }
            cursor.close();
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<>(Persona.this,
                android.R.layout.simple_list_item_1, list_personas);
        personas.setAdapter(adapter);

        database.close();
    }
}

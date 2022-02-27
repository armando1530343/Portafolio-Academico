package com.example.vannessa.cine_servicio;

import android.content.ContentValues;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class Peliculas extends AppCompatActivity {

    EditText id, titulo, horarios, director, protagonistas;
    Spinner genero, clasif, cine;

    String name_db = "cine_service.db";
    String tabla = "peliculas";

    Button agregar, consultar, actualizar, borrar;
    AlertDialog.Builder ADX;
    AlertDialog AD;
    DataBase db;
    SQLiteDatabase sqLiteDatabase;
    Cursor cursor;

    ArrayList<String> list_cine = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_peliculas);

        genero = (Spinner)findViewById(R.id.genero);
        clasif = (Spinner)findViewById(R.id.clasif);
        cine = (Spinner)findViewById(R.id.cine);

        agregar = (Button)findViewById(R.id.agregar);
        consultar = (Button)findViewById(R.id.consulta);
        actualizar = (Button)findViewById(R.id.actualiza);
        borrar = (Button)findViewById(R.id.borrar);

        id = (EditText)findViewById(R.id.id);
        titulo = (EditText)findViewById(R.id.titulo);
        horarios = (EditText)findViewById(R.id.horario);
        director = (EditText)findViewById(R.id.director);
        protagonistas = (EditText)findViewById(R.id.protagonistas);

        String [] _genero = {"Historia", "Comedia", "Ciencia Ficcion", "Animacion", "Terror"};
        String [] _clasif = {"Menores de 18 años", "Mayores de 18 años"};

        ArrayAdapter<String> adapter1 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, _genero);
        genero.setAdapter(adapter1);
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, _clasif);
        clasif.setAdapter(adapter2);

        db = new DataBase(this, name_db, null, 1);
        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        consulta();
        ArrayAdapter<String> adapter3 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, list_cine);
        cine.setAdapter(adapter3);

        agregar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && titulo.getText().length() > 0 && horarios.getText().length() > 0 &&
                        director.getText().length() > 0 && protagonistas.getText().length() > 0 &&
                        genero.getCount() > 0 && clasif.getCount() > 0 && cine.getCount() > 0){

                    if(db.getWritableDatabase() != null){
                        try{
                            ContentValues values = new ContentValues();
                            values.put("id", id.getText().toString());
                            values.put("titulo", titulo.getText().toString());
                            values.put("horario", horarios.getText().toString());
                            values.put("director", director.getText().toString());
                            values.put("protagonistas", protagonistas.getText().toString());
                            values.put("genero", genero.getSelectedItem().toString());
                            values.put("clasificacion", clasif .getSelectedItem().toString());
                            values.put("cine", cine.getSelectedItem().toString());

                            sqLiteDatabase = db.getWritableDatabase();
                            sqLiteDatabase.insert(tabla, null, values);
                            sqLiteDatabase.close();
                            AD.setMessage("Se inserto la pelicula");
                            AD.show();

                            id.setText("");
                            titulo.setText("");
                            horarios.setText("");
                            director.setText("");
                            protagonistas.setText("");
                        }
                        catch(Exception e){
                            AD.setMessage(e.getMessage());
                            AD.show();
                        }
                    }

                }
                else{
                    AD.setMessage("Faltan datos por rellenar");
                    AD.show();
                }

            }
        });

        consultar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                titulo.setText("");
                horarios.setText("");
                director.setText("");
                protagonistas.setText("");
                if(id.getText().length() > 0){
                    if(db.getReadableDatabase() != null){

                        sqLiteDatabase = db.getReadableDatabase();
                        cursor = sqLiteDatabase.rawQuery("select * from " + tabla + " where id = " + id.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            titulo.setText(cursor.getString(1));
                            horarios.setText(cursor.getString(2));
                            director.setText(cursor.getString(3));
                            protagonistas.setText(cursor.getString(4));

                            String [] _genero = {cursor.getString(5), "Historia", "Comedia", "Ciencia Ficcion", "Animacion", "Terror"};
                            String [] _clasif = {cursor.getString(6), "Menores de 18 años", "Mayores de 18 años"};

                            ArrayAdapter<String> adapter1 = new ArrayAdapter<String>(Peliculas.this, android.R.layout.simple_spinner_item, _genero);
                            genero.setAdapter(adapter1);
                            ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Peliculas.this, android.R.layout.simple_spinner_item, _clasif);
                            clasif.setAdapter(adapter2);

                            String [] c = new String[list_cine.size()+1];
                            c[0] = cursor.getString(4);
                            for(int i = 0; i < list_cine.size(); i++)
                                c[i] = list_cine.get(i);
                            ArrayAdapter<String> adapter3 = new ArrayAdapter<String>(Peliculas.this,
                                    android.R.layout.simple_spinner_item, c);
                            cine.setAdapter(adapter3);
                        }
                        else{
                            AD.setMessage("Id falso");
                            AD.show();
                        }
                        cursor.close();
                        sqLiteDatabase.close();
                    }

                }
                else{
                    AD.setMessage("Ingresa ID");
                    AD.show();
                }
            }
        });

        actualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && titulo.getText().length() > 0 && horarios.getText().length() > 0 &&
                        director.getText().length() > 0 && protagonistas.getText().length() > 0 &&
                        genero.getCount() > 0 && clasif.getCount() > 0 && cine.getCount() > 0){
                    if(db.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("id", id.getText().toString());
                        values.put("titulo", titulo.getText().toString());
                        values.put("horario", horarios.getText().toString());
                        values.put("director", director.getText().toString());
                        values.put("protagonistas", protagonistas.getText().toString());
                        values.put("genero", genero.getSelectedItem().toString());
                        values.put("clasificacion", clasif .getSelectedItem().toString());
                        values.put("cine", cine.getSelectedItem().toString());

                        sqLiteDatabase = db.getWritableDatabase();
                        sqLiteDatabase.update(tabla, values,"id="+id.getText().toString(), null);
                        sqLiteDatabase.close();
                        AD.setMessage("Informacion actualizada");
                        AD.show();

                        id.setText("");
                        titulo.setText("");
                        horarios.setText("");
                        director.setText("");
                        protagonistas.setText("");
                    }

                }
                else{
                    AD.setMessage("Faltan datos por rellenar");
                    AD.show();
                }
            }
        });
        borrar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(id.getText().length() > 0){
                    if(db.getWritableDatabase() != null){

                        try{
                            sqLiteDatabase = db.getWritableDatabase();
                            String [] args = {id.getText().toString()};
                            sqLiteDatabase.execSQL("delete from peliculas where id = ?", args);
                            sqLiteDatabase.close();
                            AD.setMessage("Se elimino la pelicula");
                            AD.show();
                            id.setText("");
                            titulo.setText("");
                            horarios.setText("");
                            director.setText("");
                            protagonistas.setText("");
                        }
                        catch(Exception e){
                            AD.setMessage(e.getMessage());
                            AD.show();
                        }

                    }
                }
                else{
                    AD.setMessage("Ingresa ID");
                    AD.show();
                }

            }
        });
    }
    void consulta()
    {
        String id;
        String Fin="";
        sqLiteDatabase = db.getReadableDatabase();
        if(sqLiteDatabase != null){
            cursor = sqLiteDatabase.rawQuery("select * from cines", null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    id = cursor.getString(0);
                    list_cine.add(id);
                }
                while(cursor.moveToNext());
            }
            cursor.close();
        }

        sqLiteDatabase.close();
    }
}

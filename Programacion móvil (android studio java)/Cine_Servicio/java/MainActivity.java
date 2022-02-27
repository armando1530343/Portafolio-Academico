package com.example.vannessa.cine_servicio;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    String name_db = "cine_service.db";
    String tabla = "cines";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    DataBase db;
    SQLiteDatabase sqLiteDatabase;
    Cursor cursor;

    Button bt1, bt2;
    ListView lista_cines;

    ArrayList<String> cines = new ArrayList<String>();
    ArrayList<Integer> cines_id = new ArrayList<Integer>();
    ArrayList<String> pelis = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bt1 = (Button)findViewById(R.id.cine);
        bt2 = (Button)findViewById(R.id.pelicula);
        lista_cines = (ListView)findViewById(R.id.lista_cines);

        db = new DataBase(this, name_db, null, 1);
        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        registros();

        final String [] lista = new String[cines.size()];
        for(int i = 0; i < lista.length; i++)
            lista[i] = cines.get(i);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, lista);
        lista_cines.setAdapter(adapter);

        bt1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(MainActivity.this, Cines.class);
                startActivity(i);
            }
        });

        bt2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(MainActivity.this, Peliculas.class);
                startActivity(i);
            }
        });

        lista_cines.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                String cadena = "";
                lista_peliculas(cines_id.get(i));
                for(int j = 0; j < pelis.size(); j++)
                    cadena += pelis.get(j) + "\n\n";
                AD.setMessage("--PELICULAS--\n\n" + cadena);
                AD.show();
                pelis.clear();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();

        cines.clear();
        registros();

        String [] lista = new String[cines.size()];
        for(int i = 0; i < lista.length; i++)
            lista[i] = cines.get(i);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, lista);
        lista_cines.setAdapter(adapter);
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    void registros ()
    {
        String id, nombre, calle, numero, telefono, p1, p2, p3, p4;
        String Fin="";
        sqLiteDatabase = db.getReadableDatabase();
        if(sqLiteDatabase != null){
            cursor = sqLiteDatabase.rawQuery("select * from " + tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    id = cursor.getString(0);
                    nombre = cursor.getString(1);
                    calle = cursor.getString(2);
                    numero = cursor.getString(3);
                    telefono = cursor.getString(4);
                    p1 = cursor.getString(5);
                    p2 = cursor.getString(6);
                    p3 = cursor.getString(7);
                    p4 = cursor.getString(8);

                    cines.add("Id:" + id + " Nombre:" + nombre + " Calle:" + calle + " Num:" + numero +
                            " Tel:" + telefono + " Espectador: $" + p1 + " Jubilado: $" + p2 +  " Festivos: $" + p3 +
                            " Estudiante: $" + p4);
                    cines_id.add(Integer.parseInt(id));
                }
                while(cursor.moveToNext());

            }
            cursor.close();
        }
        //lista.setText(Fin);
        sqLiteDatabase.close();
    }
    void lista_peliculas (int id_cine)
    {
        String id, titulo, horario, director, genero, protagonistas, clasificacion;
        String Fin="";
        sqLiteDatabase = db.getReadableDatabase();
        if(sqLiteDatabase != null){
            cursor = sqLiteDatabase.rawQuery("select * from peliculas where cine = " + id_cine, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    id = cursor.getString(0);
                    titulo = cursor.getString(1);
                    horario = cursor.getString(2);
                    director = cursor.getString(3);
                    genero = cursor.getString(4);
                    protagonistas = cursor.getString(5);
                    clasificacion = cursor.getString(6);

                    pelis.add(id + ", " + titulo + ", " + horario + ", " + director + ", " + genero + ", " + protagonistas + ", " + clasificacion);
                }
                while(cursor.moveToNext());

            }
            cursor.close();
        }
        //lista.setText(Fin);
        sqLiteDatabase.close();
    }


}

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

import java.util.ArrayList;

public class Salidas extends AppCompatActivity {

    String nombre_bd = "club.db";

    Button btn1, btn2, btn3, btn4;
    EditText id, fecha, hora, destino;
    Spinner barco, patron;
    ListView salidas;

    String tabla = "Salidas";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    AgendaSqlite sqlite;
    SQLiteDatabase database;
    Cursor cursor;
    ArrayList<String> list_salidas = new ArrayList<String>();
    ArrayList<String> personas = new ArrayList<String>();
    ArrayList<String> barcos = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_salidas);
        btn1 = (Button)findViewById(R.id.btn1);
        btn2 = (Button)findViewById(R.id.btn2);
        btn3 = (Button)findViewById(R.id.btn3);
        btn4 = (Button)findViewById(R.id.btn4);

        id = (EditText)findViewById(R.id.id);
        fecha = (EditText)findViewById(R.id.fecha);
        hora = (EditText)findViewById(R.id.hora);
        destino = (EditText)findViewById(R.id.destino);
        barco = (Spinner)findViewById(R.id.barco);
        patron = (Spinner)findViewById(R.id.patron);
        salidas = (ListView)findViewById(R.id.barcos);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        sqlite = new AgendaSqlite(this, nombre_bd, null, 1 );

        /*try{
            getTabla("Persona");
            getTabla("Barco");
        }
        catch (Exception e){
            AD.setMessage(e.getMessage());
            AD.show();
        }*/
        getTabla("Persona");
        getTabla("Barco");




        ArrayAdapter<String> adapter1 = new ArrayAdapter<String>(Salidas.this,
                android.R.layout.simple_spinner_item, personas);
        patron.setAdapter(adapter1);
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Salidas.this,
                android.R.layout.simple_spinner_item, barcos);
        barco.setAdapter(adapter2);



        RegistrosSalidas();
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && fecha.getText().length() > 0 && hora.getText().length() > 0
                        && destino.getText().length() > 0 && barco.getCount() > 0 && patron.getCount() > 0){

                    if(sqlite.getWritableDatabase() != null){
                        //database.close();
                        if(!validar(id.getText().toString())){
                            ContentValues values = new ContentValues();
                            values.put("id", id.getText().toString());
                            values.put("fecha_salida", fecha.getText().toString());
                            values.put("hora_salida", hora.getText().toString());
                            values.put("destino", destino.getText().toString());
                            values.put("barco", barco.getSelectedItem().toString());
                            values.put("patron", patron.getSelectedItem().toString());

                            database = sqlite.getWritableDatabase();
                            database.insert(tabla, null, values);
                            database.close();
                            RegistrosSalidas();
                            AD.setMessage("Se añadió correctamente");
                            AD.show();

                            id.setText("");
                            fecha.setText("");
                            hora.setText("");
                            destino.setText("");

                        }
                        else{
                            AD.setMessage("Ya existe el Id");
                            AD.show();
                        }
                    }

                }
            }
        });
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                fecha.setText("");
                hora.setText("");
                destino.setText("");
                if(id.getText().length() > 0){
                    if(sqlite.getReadableDatabase() != null){

                        database = sqlite.getReadableDatabase();
                        cursor = database.rawQuery("select * from " + tabla +
                                " where id = " + id.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            fecha.setText(cursor.getString(1));
                            hora.setText(cursor.getString(2));
                            destino.setText(cursor.getString(3));

                            int n = barcos.size();
                            String [] b = new String[n+1];
                            b[0] = cursor.getString(4);
                            for(int i = 0; i < n; i++)
                                b[i+1] = barcos.get(i);
                            ArrayAdapter<String> adapter1 = new ArrayAdapter<String>(Salidas.this,
                                    android.R.layout.simple_spinner_item, b);
                            barco.setAdapter(adapter1);

                            int x = personas.size();
                            String [] p = new String[x+1];
                            p[0] = cursor.getString(5);
                            for(int i = 0; i < n; i++)
                                p[i+1] = personas.get(i);
                            ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Salidas.this,
                                    android.R.layout.simple_spinner_item, p);
                            patron.setAdapter(adapter2);


                        }
                        else{
                            AD.setMessage("No hay Id");
                            AD.show();
                        }
                        cursor.close();
                        database.close();
                    }

                }
                else{
                    AD.setMessage("Debes poner un Id");
                    AD.show();
                }
            }
        });
        btn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && fecha.getText().length() > 0 && hora.getText().length() > 0
                        && destino.getText().length() > 0 && barco.getCount() > 0 && patron.getCount() > 0){
                    if(sqlite.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("id", id.getText().toString());
                        values.put("fecha_salida", fecha.getText().toString());
                        values.put("hora_salida", hora.getText().toString());
                        values.put("destino", destino.getText().toString());
                        values.put("barco", barco.getSelectedItem().toString());
                        values.put("patron", patron.getSelectedItem().toString());

                        database = sqlite.getWritableDatabase();
                        database.update(tabla, values,"id="+id.getText().toString(), null);
                        database.close();
                        RegistrosSalidas();
                        AD.setMessage("Se actualizo la tabla Salidas");
                        AD.show();

                        id.setText("");
                        fecha.setText("");
                        hora.setText("");
                        destino.setText("");
                    }

                }
            }
        });
        btn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(id.getText().length() > 0){
                    if(sqlite.getWritableDatabase() != null){

                        database = sqlite.getWritableDatabase();
                        String [] args = {id.getText().toString()};
                        database.execSQL("delete from Salidas where id = ?", args);

                        database.close();
                        RegistrosSalidas();
                        AD.setMessage("Se borro la Salida");
                        AD.show();
                        id.setText("");
                        fecha.setText("");
                        hora.setText("");
                        destino.setText("");

                    }
                }
                else{
                    AD.setMessage("Debes poner un Id");
                    AD.show();
                }

            }
        });





    }

    void getTabla(String nombre_tabla)
    {
        String id;
        ArrayList<String> list = new ArrayList<>();
        database = sqlite.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + nombre_tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    id = cursor.getString(0);
                    list.add(id);

                }
                while(cursor.moveToNext());
            }
            cursor.close();
        }
        if(nombre_tabla.equals("Persona")){
            personas = list;
        }
        else{
            barcos = list;
        }

        database.close();
    }
    boolean validar (String id)
    {
        String Fin="";
        SQLiteDatabase db = sqlite.getReadableDatabase();
        cursor = db.rawQuery("select * from " + tabla + " where id = " + id , null);

        if (cursor.getCount() > 0) {
            return true;
        }
        cursor.close();
        db.close();

        return false;
    }
    void RegistrosSalidas ()
    {
        list_salidas.clear();
        String id, fecha, hora, destino, barco, patron;
        String Fin="";
        database = sqlite.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    id = cursor.getString(0);
                    fecha = cursor.getString(1);
                    hora = cursor.getString(2);
                    destino = cursor.getString(3);
                    barco = cursor.getString(4);
                    patron = cursor.getString(5);
                    list_salidas.add(id + ", " + fecha + ", " + hora + ", " + destino + ", " + barco + ", " + patron + "\n");
                }
                while(cursor.moveToNext());

            }
            cursor.close();
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<>(Salidas.this,
                android.R.layout.simple_list_item_1, list_salidas);
        salidas.setAdapter(adapter);

        database.close();
    }
}

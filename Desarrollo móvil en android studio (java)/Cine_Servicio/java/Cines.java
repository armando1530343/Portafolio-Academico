package com.example.vannessa.cine_servicio;

import android.content.ContentValues;
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
public class Cines extends AppCompatActivity {

    String name_db = "cine_service.db";
    String tabla = "cines";

    Button agregar, consultar, actualizar, borrar;
    EditText id, nombre, calle, numero, telefono, p1, p2, p3, p4;

    AlertDialog.Builder ADX;
    AlertDialog AD;
    DataBase db;
    SQLiteDatabase sqLiteDatabase;
    Cursor cursor;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cines);

        agregar = (Button)findViewById(R.id.add);
        consultar = (Button)findViewById(R.id.consulta);
        actualizar = (Button)findViewById(R.id.actualiza);
        borrar = (Button)findViewById(R.id.borrar);

        id = (EditText)findViewById(R.id.id);
        nombre = (EditText)findViewById(R.id.nombre);
        calle = (EditText)findViewById(R.id.calle);
        numero = (EditText)findViewById(R.id.numero);
        telefono = (EditText)findViewById(R.id.telefono);
        p1 = (EditText)findViewById(R.id.precio1);
        p2 = (EditText)findViewById(R.id.precio2);
        p3 = (EditText)findViewById(R.id.precio3);
        p4 = (EditText)findViewById(R.id.precio4);


        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        db = new DataBase(this, name_db, null, 1);

        agregar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && nombre.getText().length() > 0 && calle.getText().length() > 0 &&
                        numero.getText().length() > 0 && telefono.getText().length() > 0 && p1.getText().length() > 0 &&
                        p2.getText().length() > 0 && p3.getText().length() > 0 && p4.getText().length() > 0){

                    if(db.getWritableDatabase() != null){
                        try{
                            ContentValues values = new ContentValues();
                            values.put("id", id.getText().toString());
                            values.put("nombre", nombre.getText().toString());
                            values.put("calle", calle.getText().toString());
                            values.put("numero", numero.getText().toString());
                            values.put("telefono", telefono.getText().toString());
                            values.put("precio1", p1.getText().toString());
                            values.put("precio2", p2.getText().toString());
                            values.put("precio3", p3.getText().toString());
                            values.put("precio4", p4.getText().toString());

                            sqLiteDatabase = db.getWritableDatabase();
                            sqLiteDatabase.insert(tabla, null, values);
                            sqLiteDatabase.close();
                            AD.setMessage("Se inserto el cine");
                            AD.show();

                            id.setText("");
                            nombre.setText("");
                            calle.setText("");
                            numero.setText("");
                            telefono.setText("");
                            p1.setText("");
                            p2.setText("");
                            p3.setText("");
                            p4.setText("");
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
                nombre.setText("");
                calle.setText("");
                numero.setText("");
                telefono.setText("");
                p1.setText("");
                p2.setText("");
                p3.setText("");
                p4.setText("");
                if(id.getText().length() > 0){
                    if(db.getReadableDatabase() != null){

                        sqLiteDatabase = db.getReadableDatabase();
                        cursor = sqLiteDatabase.rawQuery("select * from " + tabla + " where id = " + id.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            nombre.setText(cursor.getString(1));
                            calle.setText(cursor.getString(2));
                            numero.setText(cursor.getString(3));
                            telefono.setText(cursor.getString(4));
                            p1.setText(cursor.getString(5));
                            p2.setText(cursor.getString(6));
                            p3.setText(cursor.getString(7));
                            p4.setText(cursor.getString(8));
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
                if(id.getText().length() > 0 && nombre.getText().length() > 0 && calle.getText().length() > 0 &&
                        numero.getText().length() > 0 && telefono.getText().length() > 0 && p1.getText().length() > 0 &&
                        p2.getText().length() > 0 && p3.getText().length() > 0 && p4.getText().length() > 0){
                    if(db.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("id", id.getText().toString());
                        values.put("nombre", nombre.getText().toString());
                        values.put("calle", calle.getText().toString());
                        values.put("numero", numero.getText().toString());
                        values.put("telefono", telefono.getText().toString());
                        values.put("precio1", p1.getText().toString());
                        values.put("precio2", p2.getText().toString());
                        values.put("precio3", p3.getText().toString());
                        values.put("precio4", p4.getText().toString());

                        sqLiteDatabase = db.getWritableDatabase();
                        sqLiteDatabase.update(tabla, values,"id="+id.getText().toString(), null);
                        sqLiteDatabase.close();
                        AD.setMessage("Informacion actualizada");
                        AD.show();

                        id.setText("");
                        nombre.setText("");
                        calle.setText("");
                        numero.setText("");
                        telefono.setText("");
                        p1.setText("");
                        p2.setText("");
                        p3.setText("");
                        p4.setText("");
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
                            sqLiteDatabase.execSQL("delete from peliculas where cine = ?", args);
                            sqLiteDatabase.execSQL("delete from cines where id = ?", args);
                            sqLiteDatabase.close();
                            AD.setMessage("Se elimino el cine");
                            AD.show();
                            id.setText("");
                            nombre.setText("");
                            calle.setText("");
                            numero.setText("");
                            telefono.setText("");
                            p1.setText("");
                            p2.setText("");
                            p3.setText("");
                            p4.setText("");
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
}

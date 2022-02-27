package com.example.armando.gabineteabogados;

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

public class Abogados extends AppCompatActivity {

    String database_name = "gabinete.db";

    Button agregar, consultar, actualizar, eliminar;
    EditText id, nombre, telefono;
    TextView lista;

    String tabla = "ABOGADOS";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    GestionBD gestion;
    SQLiteDatabase database;
    Cursor cursor;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_abogados);

        agregar = (Button)findViewById(R.id.agregar_btn);
        consultar = (Button)findViewById(R.id.consultar_btn);
        actualizar = (Button)findViewById(R.id.actualizar_btn);
        eliminar = (Button)findViewById(R.id.eliminar_btn);

        id = (EditText)findViewById(R.id.id);
        nombre = (EditText)findViewById(R.id.nombre);
        telefono = (EditText)findViewById(R.id.telefono);

        lista = (TextView)findViewById(R.id.lista);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        gestion = new GestionBD(this, database_name, null, 1);

        consultaTabla();




        agregar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && nombre.getText().length() > 0 && telefono.getText().length() > 0){

                    if(gestion.getWritableDatabase() != null){
                        //database.close();
                        if(existeId(id.getText().toString())==false){
                            ContentValues values = new ContentValues();
                            values.put("id", id.getText().toString());
                            values.put("nombre", nombre.getText().toString());
                            values.put("telefono", telefono.getText().toString());

                            database = gestion.getWritableDatabase();
                            database.insert(tabla, null, values);
                            database.close();
                            consultaTabla();
                            AD.setMessage("Datos insertados");
                            AD.show();

                            id.setText("");
                            nombre.setText("");
                            telefono.setText("");
                        }
                        else{
                            AD.setMessage("El Id ya existe");
                            AD.show();
                        }
                    }

                }
                else{
                    AD.setMessage("Campos incompletos");
                    AD.show();
                }

            }
        });

        consultar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                nombre.setText("");
                telefono.setText("");
                if(id.getText().length() > 0){
                    if(gestion.getReadableDatabase() != null){

                        database = gestion.getReadableDatabase();
                        cursor = database.rawQuery("select * from " + tabla + " where id = " + id.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            nombre.setText(cursor.getString(1));
                            telefono.setText(cursor.getString(2));
                        }
                        else{
                            AD.setMessage("No existe el Id");
                            AD.show();
                        }
                        cursor.close();
                        database.close();
                    }

                }
                else{
                    AD.setMessage("Introduce un Id");
                    AD.show();
                }
            }
        });

        actualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && nombre.getText().length() > 0 && telefono.getText().length() > 0){
                    if(gestion.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("id", id.getText().toString());
                        values.put("nombre", nombre.getText().toString());
                        values.put("telefono", telefono.getText().toString());

                        database = gestion.getWritableDatabase();
                        database.update(tabla, values,"id="+id.getText().toString(), null);
                        database.close();
                        consultaTabla();
                        AD.setMessage("Datos actualizados");
                        AD.show();

                        id.setText("");
                        nombre.setText("");
                        telefono.setText("");
                    }

                }
                else{
                    AD.setMessage("Campos incompletos");
                    AD.show();
                }
            }
        });

        eliminar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(id.getText().length() > 0){
                    if(gestion.getWritableDatabase() != null){

                        try{
                            database = gestion.getWritableDatabase();
                            String [] args = {id.getText().toString()};
                            database.execSQL("delete from ASUNTOS where abogado = ?", args);
                            database.execSQL("delete from ABOGADOS where id = ?", args);
                            database.close();
                            consultaTabla();
                            AD.setMessage("Se elimino el abogado y asuntos relacionados");
                            AD.show();
                            id.setText("");
                            nombre.setText("");
                            telefono.setText("");
                        }
                        catch(Exception e){
                            AD.setMessage(e.getMessage());
                            AD.show();
                        }

                    }
                }
                else{
                    AD.setMessage("Introduce Id");
                    AD.show();
                }

            }
        });
    }

    void consultaTabla ()
    {
        String _id, _nombre, _telefono;
        String Fin="";
        database = gestion.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + tabla, null);

            if (cursor.getCount() > 0) {

                cursor.moveToFirst();

                do{
                    _id = cursor.getString(0);
                    _nombre = cursor.getString(1);
                    _telefono = cursor.getString(2);
                    Fin += ("Id:" + _id + "   Nombre:" + _nombre + "   Telefono:" + _telefono + "\n");
                }
                while(cursor.moveToNext());
            }
            cursor.close();
        }
        lista.setText(Fin);
        database.close();
    }

    boolean existeId (String id_)
    {
        String _id;
        String Fin="";
        SQLiteDatabase db = gestion.getReadableDatabase();
        cursor = db.rawQuery("select * from ABOGADOS where id = " + id_ , null);

        if (cursor.getCount() > 0) {
            return true;
        }
        cursor.close();
        db.close();

        return false;
    }
}

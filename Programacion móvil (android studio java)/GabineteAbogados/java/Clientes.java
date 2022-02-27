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
import android.widget.Toast;

public class Clientes extends AppCompatActivity {

    String database_name = "gabinete.db";

    Button agregar, consultar, actualizar, eliminar;
    EditText id, dni, nombre, direccion;
    TextView lista;

    String tabla = "CLIENTES";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    GestionBD gestion;
    SQLiteDatabase database;
    Cursor cursor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_clientes);

        agregar = (Button)findViewById(R.id.agregar_btn);
        consultar = (Button)findViewById(R.id.consultar_btn);
        actualizar = (Button)findViewById(R.id.actualizar_btn);
        eliminar = (Button)findViewById(R.id.eliminar_btn);

        id = (EditText)findViewById(R.id.id);
        dni = (EditText)findViewById(R.id.dni);
        nombre = (EditText)findViewById(R.id.nombre);
        direccion = (EditText)findViewById(R.id.direccion);

        lista = (TextView)findViewById(R.id.lista);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        gestion = new GestionBD(this, database_name, null, 1);

        consultaTabla();




        agregar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(id.getText().length() > 0 && dni.getText().length() > 0 && nombre.getText().length() > 0 &&
                        direccion.getText().length() > 0){

                    if(gestion.getWritableDatabase() != null){
                        //database.close();
                        if(existeId(id.getText().toString())==false){
                            ContentValues values = new ContentValues();
                            values.put("id", id.getText().toString());
                            values.put("nombre", nombre.getText().toString());
                            values.put("dni", dni.getText().toString());
                            values.put("direccion", direccion.getText().toString());

                            database = gestion.getWritableDatabase();
                            database.insert(tabla, null, values);
                            database.close();
                            consultaTabla();
                            AD.setMessage("Datos insertados");
                            AD.show();

                            id.setText("");
                            dni.setText("");
                            nombre.setText("");
                            direccion.setText("");
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
                dni.setText("");
                nombre.setText("");
                direccion.setText("");
                if(id.getText().length() > 0){
                    if(gestion.getReadableDatabase() != null){

                        database = gestion.getReadableDatabase();
                        cursor = database.rawQuery("select * from " + tabla + " where id = " + id.getText().toString(), null);
                        if(cursor.getCount() > 0){
                            cursor.moveToFirst();
                            dni.setText(cursor.getString(2));
                            nombre.setText(cursor.getString(1));
                            direccion.setText(cursor.getString(3));
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
                if(id.getText().length() > 0 && dni.getText().length() > 0 && nombre.getText().length() > 0 &&
                        direccion.getText().length() > 0){
                    if(gestion.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("id", id.getText().toString());
                        values.put("nombre", nombre.getText().toString());
                        values.put("dni", dni.getText().toString());
                        values.put("direccion", direccion.getText().toString());

                        database = gestion.getWritableDatabase();
                        database.update(tabla, values,"id="+id.getText().toString(), null);
                        database.close();
                        consultaTabla();
                        AD.setMessage("Datos actualizados");
                        AD.show();

                        id.setText("");
                        dni.setText("");
                        nombre.setText("");
                        direccion.setText("");
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
                            database.execSQL("delete from ASUNTOS where cliente = ?", args);
                            database.execSQL("delete from CLIENTES where id = ?", args);
                            database.close();
                            consultaTabla();
                            AD.setMessage("Se elimino el cliente y asuntos relacionados");
                            AD.show();
                            id.setText("");
                            dni.setText("");
                            nombre.setText("");
                            direccion.setText("");
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
        String _id, _dni, _nombre, _direccion;
        String Fin="";
        database = gestion.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    _id = cursor.getString(0);
                    _dni = cursor.getString(2);
                    _nombre = cursor.getString(1);
                    _direccion = cursor.getString(3);
                    Fin += ("Id:" + _id + "   DNI:" + _dni + "   Name:" + _nombre + "   Dir:" + _direccion + "\n");
                }
                while(cursor.moveToNext());

            }
            else{
                Toast.makeText(Clientes.this, "No hay registros", Toast.LENGTH_LONG);
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
        cursor = db.rawQuery("select * from " + tabla + " where id = " + id_ , null);

        if (cursor.getCount() > 0) {
            return true;
        }
        cursor.close();
        db.close();

        return false;
    }
}

package com.example.armando.gabineteabogados;

import android.app.DatePickerDialog;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Calendar;

public class Asuntos extends AppCompatActivity {

    private int dia_actual, mes_actual, anio_actual, hora_actual, minuto_actual;

    String database_name = "gabinete.db";

    Button agregar, consultar, actualizar, eliminar;
    EditText no_exp, fecha_inicio, fecha_fin;
    Spinner abogado, cliente, estado;
    TextView lista;

    String tabla = "ASUNTOS";

    AlertDialog.Builder ADX;
    AlertDialog AD;
    GestionBD gestion;
    SQLiteDatabase database;
    Cursor cursor;

    String fecha;
    EditText fecha_edit;
    ArrayList<String> abogados = new ArrayList<String>();
    ArrayList<String> clientes = new ArrayList<String>();
    String [] est = {"En tramite", "Archivado"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_asuntos);

        no_exp = (EditText)findViewById(R.id.exp);
        fecha_inicio = (EditText)findViewById(R.id.fecha_inicio);
        fecha_fin = (EditText)findViewById(R.id.fecha_fin);
        abogado = (Spinner) findViewById(R.id.id_abogado);
        cliente = (Spinner) findViewById(R.id.id_cliente);
        estado = (Spinner) findViewById(R.id.estado);
        lista = (TextView)findViewById(R.id.lista);

        agregar = (Button)findViewById(R.id.agregar_btn);
        consultar = (Button)findViewById(R.id.consultar_btn);
        actualizar = (Button)findViewById(R.id.actualizar_btn);
        eliminar = (Button)findViewById(R.id.eliminar_btn);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        fecha_inicio.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clic_fecha(fecha_inicio);
            }
        });

        fecha_fin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clic_fecha(fecha_fin);
            }
        });

        gestion = new GestionBD(this, database_name, null, 1);

        consultaTabla();

        consulta("ABOGADOS");
        consulta("CLIENTES");

        ArrayAdapter<String> adapter1 = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, abogados);
        abogado.setAdapter(adapter1);

        ArrayAdapter<String> adapter2 = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, clientes);
        cliente.setAdapter(adapter2);

        ArrayAdapter<String> adapter3 = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, est);
        estado.setAdapter(adapter3);

        agregar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(no_exp.getText().length() > 0 && fecha_inicio.getText().length() > 0 && fecha_fin.getText().length() > 0 &&
                        abogado.getCount() > 0 && cliente.getCount() > 0){

                    if(gestion.getWritableDatabase() != null){
                        //database.close();
                        if(existeId(no_exp.getText().toString())==false){
                            ContentValues values = new ContentValues();
                            values.put("no_exp", no_exp.getText().toString());
                            values.put("fecha_inicio", fecha_inicio.getText().toString());
                            values.put("fecha_fin", fecha_fin.getText().toString());
                            values.put("estado", estado.getSelectedItem().toString());
                            values.put("abogado", abogado.getSelectedItem().toString());
                            values.put("cliente", cliente.getSelectedItem().toString());

                            database = gestion.getWritableDatabase();
                            database.insert(tabla, null, values);
                            database.close();
                            consultaTabla();
                            AD.setMessage("Datos insertados");
                            AD.show();

                            no_exp.setText("");
                            fecha_inicio.setText("");
                            fecha_fin.setText("");
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
                //no_exp.setText("");
                fecha_inicio.setText("");
                fecha_fin.setText("");
                if(no_exp.getText().length() > 0){
                    if(gestion.getReadableDatabase() != null){

                        database = gestion.getReadableDatabase();
                        cursor = database.rawQuery("select * from " + tabla + " where no_exp = " +
                                no_exp.getText().toString(), null);
                        if(cursor.getCount() > 0){

                            cursor.moveToFirst();
                            //no_exp.setText(cursor.getString(0));
                            fecha_inicio.setText(cursor.getString(1));
                            fecha_fin.setText(cursor.getString(2));
                            String [] est1 = new String[]{cursor.getString(3), "En tramite", "Archivado"};
                            ArrayAdapter<String> adapter1 = new ArrayAdapter<String>(Asuntos.this,
                                    android.R.layout.simple_spinner_item, est1);
                            estado.setAdapter(adapter1);

                            String [] abo = new String[abogados.size()+1];
                            abo[0] = cursor.getString(4);
                            for(int i = 0; i < abogados.size(); i++)
                                abo[i] = abogados.get(i);
                            ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(Asuntos.this,
                                    android.R.layout.simple_spinner_item, abo);
                            abogado.setAdapter(adapter2);

                            String [] cli = new String[clientes.size()+1];
                            cli[0] = cursor.getString(5);
                            for(int i = 0; i < clientes.size(); i++)
                                cli[i] = clientes.get(i);
                            ArrayAdapter<String> adapter3 = new ArrayAdapter<String>(Asuntos.this,
                                    android.R.layout.simple_spinner_item, cli);
                            cliente.setAdapter(adapter3);
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
                if(no_exp.getText().length() > 0 && fecha_inicio.getText().length() > 0 && fecha_fin.getText().length() > 0 &&
                        estado.getCount() > 0 && abogado.getCount() > 0 && cliente.getCount() > 0){
                    if(gestion.getWritableDatabase() != null){

                        ContentValues values = new ContentValues();
                        values.put("no_exp", no_exp.getText().toString());
                        values.put("fecha_inicio", fecha_inicio.getText().toString());
                        values.put("fecha_fin", fecha_fin.getText().toString());
                        values.put("estado", estado.getSelectedItem().toString());
                        values.put("abogado", abogado.getSelectedItem().toString());
                        values.put("cliente", cliente.getSelectedItem().toString());

                        database = gestion.getWritableDatabase();
                        database.update(tabla, values,"no_exp="+no_exp.getText().toString(), null);
                        database.close();
                        consultaTabla();
                        AD.setMessage("Datos actualizados");
                        AD.show();

                        no_exp.setText("");
                        fecha_inicio.setText("");
                        fecha_fin.setText("");
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

                if(no_exp.getText().length() > 0){
                    if(gestion.getWritableDatabase() != null){

                        database = gestion.getWritableDatabase();
                        String [] args = {no_exp.getText().toString()};
                        database.execSQL("delete from ASUNTOS where no_exp = ?", args);
                        database.close();
                        consultaTabla();
                        AD.setMessage("Se elimino el Asunto");
                        AD.show();
                        no_exp.setText("");
                        fecha_inicio.setText("");
                        fecha_fin.setText("");

                    }
                }
                else{
                    AD.setMessage("Introduce No. Expediente");
                    AD.show();
                }

            }
        });



    }
    public void clic_fecha(EditText e){
        final Calendar c = Calendar.getInstance();
        dia_actual = c.get(Calendar.DAY_OF_MONTH);
        mes_actual = c.get(Calendar.MONTH);
        anio_actual = c.get(Calendar.YEAR);

        fecha_edit = e;

        DatePickerDialog datePickerDialog = new DatePickerDialog(this, new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker datePicker, int i, int i1, int i2) {
                fecha_edit.setText(i2 + "/" + (i1+1) + "/" + i);
                //dia = i; mes = i1; anio = i2;
            }

        }, dia_actual, mes_actual, anio_actual);

        //e.setText(fecha);
        datePickerDialog.show();

    }

    void consulta (String t)
    {
        String _id, _nombre;
        String Fin="";
        database = gestion.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + t, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    _id = cursor.getString(0);
                    _nombre = cursor.getString(1);
                    if(t.equals("ABOGADOS"))
                        abogados.add(_id);
                    if(t.equals("CLIENTES"))
                        clientes.add(_id);

                }
                while(cursor.moveToNext());
            }
            cursor.close();
        }

        database.close();
    }
    void consultaTabla ()
    {
        String exp, fi, ff, es, ab, cl;
        String Fin="";
        database = gestion.getReadableDatabase();
        if(database != null){
            cursor = database.rawQuery("select * from " + tabla, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    exp = cursor.getString(0);
                    fi = cursor.getString(1);
                    ff = cursor.getString(2);
                    es = cursor.getString(3);
                    ab = cursor.getString(4);
                    cl = cursor.getString(5);
                    Fin += ("No.exp:" + exp + "   Inicio:" + fi + "   Fin:" + ff + "   Est:" + es + "   Abogado:" + ab +
                            "   Cliente:" + cl + "\n");
                }
                while(cursor.moveToNext());

            }
            else{
                Toast.makeText(Asuntos.this, "No hay registros", Toast.LENGTH_LONG);
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
        cursor = db.rawQuery("select * from " + tabla + " where no_exp = " + id_ , null);

        if (cursor.getCount() > 0) {
            return true;
        }
        cursor.close();
        db.close();

        return false;
    }
}

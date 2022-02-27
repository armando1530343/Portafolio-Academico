package com.example.armando.buscador;

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
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    EditText buscarEtx;
    Button buscarBtn;
    ListView lista;

    //SOLO BASTA CON CAMBIAR ESTAS 3 VARIABLES PARA ADAPTAR A CUALQUIER TABLA------
    String db_name = "prueba.db";
    String tabla = "tabla1";
    String [] columnas = {"id", "nombre", "telefono"};
    //-----------------------------------------------------------------------------


    AlertDialog.Builder ADX;
    AlertDialog AD;
    SQLite sqLite;
    SQLiteDatabase database;
    Cursor cursor;

    ArrayList<String> resultados = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        buscarEtx = (EditText)findViewById(R.id.buscarEtx);
        buscarBtn = (Button)findViewById(R.id.buscarBtn);
        lista = (ListView)findViewById(R.id.lista);

        ADX = new AlertDialog.Builder(this);
        AD = ADX.create();

        sqLite = new SQLite(this, db_name, null, 1);

        //INSERTAR DATOS DE PRUEBA A LA TABLA1------------------------
        try{
            //LOS SIGUIENTES DATOS SOLO SE INSERTARON COMO PRUEBA PARA LA BUSQUEDA

            ContentValues contentValues = new ContentValues();
            contentValues.put("id", "1");
            contentValues.put("nombre", "pedro");
            contentValues.put("telefono", "1234");
            database = sqLite.getWritableDatabase();
            database.insert(tabla, null, contentValues);
            contentValues.clear();

            contentValues.put("id", "2");
            contentValues.put("nombre", "luis");
            contentValues.put("telefono", "1234567");
            database.insert(tabla, null, contentValues);
            contentValues.clear();

            contentValues.put("id", "3");
            contentValues.put("nombre", "alejandro");
            contentValues.put("telefono", "1237");
            database.insert(tabla, null, contentValues);
            contentValues.clear();

            contentValues.put("id", "4");
            contentValues.put("nombre", "alejandra");
            contentValues.put("telefono", "567");
            database.insert(tabla, null, contentValues);
            contentValues.clear();
            database.close();
        }
        catch (Exception e){
            AD.setMessage(e.getMessage());
            AD.show();
        }

        buscarBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(buscarEtx.getText().length() > 0) {
                    busqueda(buscarEtx.getText().toString());
                    if(resultados.size() > 0){

                        String [] res = new String[resultados.size()];
                        for(int i = 0; i < resultados.size(); i++)
                            res[i] = resultados.get(i);

                        ArrayAdapter<String> adapter = new ArrayAdapter<String>(MainActivity.this,
                                android.R.layout.simple_list_item_1, res);

                        lista.setAdapter(adapter);
                        //AD.setMessage("res: "+resultados.size());
                        //AD.show();
                        resultados.clear();
                    }
                    else {
                        AD.setMessage("No hay resultados");
                        AD.show();
                    }


                }
                else{
                    AD.setMessage("Introduce texto");
                    AD.show();
                }
            }
        });

    }

    void busqueda (String texto)
    {


        String [] columns = new String[columnas.length];
        String Fin="";
        database = sqLite.getReadableDatabase();
        if(database != null){

            String strsql = "select * from " + tabla + " where ";
            for(int i = 0; i < columnas.length; i++) {
                strsql += columnas[i] + " like '" + texto + "%' ";
                strsql += i == columnas.length-1 ? "" : "or ";
            }

            //AD.setMessage(strsql);
            //AD.show();


            //SE SELECCIONAN TODOS LOS REGISTROS DE LA TABLA QUE COINCIDAN CON LA REFERENCIA TEXTO
            cursor = database.rawQuery(strsql, null);
            if (cursor.getCount() > 0) {
                cursor.moveToFirst();
                do{
                    String registro = "";
                    //SE OBTIENEN LOS CAMPOS DE LA TABLA
                    for(int i = 0; i < columnas.length; i++){
                        columns[i] = cursor.getString(i);
                        registro+= columns[i] + ", ";
                    }
                    resultados.add(registro);

                }
                while(cursor.moveToNext());
            }
            cursor.close();
        }

        database.close();
    }
}

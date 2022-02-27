package com.example.armando.estadisticas_gastos;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private EditText monto, costo, descripcion;
    private TextView saldo_inicial_txt, total_gasto_txt, saldo_restante_txt;
    private ListView listView;

    private ArrayList<String> elementos;

    private Calendar fecha = Calendar.getInstance();

    private float saldo_inicial, total_gasto, saldo_restante;

    private ArrayList<String> gastos_data = new ArrayList<String>();
    private ArrayList<String> depositos_data = new ArrayList<String>();
    private ArrayList<String> conceptos_data = new ArrayList<String>();

    private ArrayList<Gastos> gastos = new ArrayList<Gastos>();
    private ArrayList<Depositos> depositos = new ArrayList<Depositos>();
    private ArrayList<Conceptos> conceptos = new ArrayList<Conceptos>();

    int n = 4;
    private String txt1 = "gastos" + n + ".txt";
    private String txt2 = "depositos" + n + ".txt";
    private String txt3 = "conceptos" + n + ".txt";

    private String fechaActual;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        monto = (EditText)findViewById(R.id.monto_txt);
        costo = (EditText)findViewById(R.id.costo_txt);
        descripcion = (EditText)findViewById(R.id.descripcion_txt);

        saldo_inicial_txt = (TextView)findViewById(R.id.saldo_inicial);
        total_gasto_txt = (TextView)findViewById(R.id.total_gasto);
        saldo_restante_txt = (TextView)findViewById(R.id.saldo_restante);

        listView = (ListView)findViewById(R.id.lista);

        elementos = new ArrayList<String>();

        LeerContenido();

        //se obtiene el saldo mas actual
        saldo_inicial = depositos.get(depositos.size()-1).getMonto();
        saldo_inicial_txt.setText("Saldo inicial: $"+saldo_inicial);
        total_gasto_txt.setText("Total gasto: $"+total_gasto);

        saldo_restante = saldo_inicial-total_gasto;
        saldo_restante_txt.setText("Saldo restante: $"+saldo_restante);

    }

    public void depositar(View view){

        float monto_depositado = Float.parseFloat(monto.getText().toString()) + saldo_inicial;

        try{
            int index1 = depositos.size()-1;
            int index2 = gastos.size()-1;
            OutputStreamWriter archivo_deposito = new OutputStreamWriter(openFileOutput(txt2, Activity.MODE_PRIVATE));
            for(int i = 0; i < depositos.size(); i++)
                archivo_deposito.write( "" + (depositos.get(i).getId()) + "," + depositos.get(i).monto + "," + depositos.get(i).getId_gasto() + "\n");
            archivo_deposito.write( "" + (depositos.get(index1).getId()+1) + "," + monto_depositado + "," + gastos.get(index2).getId() + "\n");
            archivo_deposito.flush();
            archivo_deposito.close();

            vaciar();
            LeerContenido();

        }
        catch(Exception ex){}

        //se obtiene el saldo mas actual
        saldo_inicial = depositos.get(depositos.size()-1).getMonto();
        saldo_restante = saldo_inicial-total_gasto;

        saldo_inicial_txt.setText("Saldo inicial: $"+saldo_inicial);
        total_gasto_txt.setText("Total gasto: $"+total_gasto);
        saldo_restante_txt.setText("Saldo restante: $"+saldo_restante);
        monto.setText("");
        monto.findFocus();
    }

    public void add(View v){
        float costo_ = Float.parseFloat(costo.getText().toString());
        String descripcion_ = descripcion.getText().toString();
        //elementos.add("-" + descripcion_ + ": $" + costo_ );

        try{
            int index = gastos.size()-1;
            int index2 = conceptos.size()-1;
            OutputStreamWriter archivo_deposito = new OutputStreamWriter(openFileOutput(txt3, Activity.MODE_PRIVATE));

            for(int i = 0; i < conceptos.size(); i++)
                archivo_deposito.write( "" + conceptos.get(i).getId() + "," + conceptos.get(i).getNombre() + "," + conceptos.get(i).getCosto() + "," + conceptos.get(i).getId_gasto() + "\n");
            archivo_deposito.write( "" + (conceptos.get(index2).getId() + 1) + "," + descripcion_ + "," + costo_ + "," + gastos.get(index).getId() + "\n");

            archivo_deposito.flush();
            archivo_deposito.close();


        }
        catch(Exception ex){}

        total_gasto += costo_;
        saldo_restante -= costo_;

        total_gasto_txt.setText("Total gasto: $"+total_gasto);
        saldo_restante_txt.setText("Saldo restante: $"+saldo_restante);

        costo.setText("");
        descripcion.setText("");
        monto.setText("");
        costo.findFocus();

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.lista_conceptos, elementos);
        listView.setAdapter(adapter);

        vaciar();
        LeerContenido();
    }

    private boolean ExisteArchivo(String [] archivos, String filename){
        for(int i = 0; i < archivos.length; i++){
            if(archivos[i].equals(filename)){
                //Toast.makeText(this, archivos[i], Toast.LENGTH_SHORT).show();
                return true;
            }
        }
        return false;
    }

    private void LeerContenido(){
        //obtener archivos de telefono
        String [] archivos = fileList();

        //VERIFICAR ARCHIVO DE GASTOS
        if(ExisteArchivo(archivos, txt1)){
            try{

                InputStreamReader archivo_gastos = new InputStreamReader(openFileInput(txt1));
                BufferedReader br = new BufferedReader(archivo_gastos);

                String linea = br.readLine();

                while(linea != null){

                    gastos_data.add(linea);
                    //Toast.makeText(this, "dato: " + linea, Toast.LENGTH_SHORT).show();
                    linea = br.readLine();

                }
                br.close();
                archivo_gastos.close();
                //Toast.makeText(this, "lectura correcta", Toast.LENGTH_SHORT).show();
            }
            catch(Exception ex){Toast.makeText(this, "error 1", Toast.LENGTH_SHORT).show();}

        }
        else{
            try{
                OutputStreamWriter archivo_gastos = new OutputStreamWriter(openFileOutput(txt1, Activity.MODE_PRIVATE));
                archivo_gastos.write("0," + fecha.get(Calendar.DAY_OF_MONTH) + "_" + (fecha.get(Calendar.MONTH)+1) + "_" + fecha.get(Calendar.YEAR) + "\n");
                archivo_gastos.flush();
                archivo_gastos.close();
                Toast.makeText(this, "Se creo gastos.txt", Toast.LENGTH_SHORT).show();
                gastos_data.add("0," + fecha.get(Calendar.DAY_OF_MONTH) + "_" + (fecha.get(Calendar.MONTH)+1) + "_" + fecha.get(Calendar.YEAR));

                OutputStreamWriter archivo_deposito = new OutputStreamWriter(openFileOutput(txt2, Activity.MODE_PRIVATE));
                archivo_deposito.write("0,0,0\n");
                archivo_deposito.flush();
                archivo_deposito.close();
                Toast.makeText(this, "Se creo depositos.txt", Toast.LENGTH_SHORT).show();
                depositos_data.add("0,0,0");

                OutputStreamWriter archivo_conceptos = new OutputStreamWriter(openFileOutput(txt3, Activity.MODE_PRIVATE));
                archivo_conceptos.write("0,0,0,0\n");
                archivo_conceptos.flush();
                archivo_conceptos.close();
                Toast.makeText(this, "Se creo conceptos.txt", Toast.LENGTH_SHORT).show();
                conceptos_data.add("0,0,0,0");
            }
            catch(Exception ex){}
        }

        //VERIFICAR ARCHIVO DE DEPOSITOS
        if(ExisteArchivo(archivos, txt2)){
            try{
                InputStreamReader archivo_deposito = new InputStreamReader(openFileInput(txt2));
                BufferedReader br = new BufferedReader(archivo_deposito);
                String linea = br.readLine();
                while(linea != null){
                    depositos_data.add(linea);
                    linea = br.readLine();

                }
                br.close();
                archivo_deposito.close();
                //Toast.makeText(this, "lectura correcta", Toast.LENGTH_SHORT).show();
            }
            catch(Exception ex){Toast.makeText(this, "error 2", Toast.LENGTH_SHORT).show();}

        }

        //VERIFICAR ARCHIVO DE CONCEPTOS
        if(ExisteArchivo(archivos, txt3)){
            try{
                InputStreamReader archivo_conceptos = new InputStreamReader(openFileInput(txt3));
                BufferedReader br = new BufferedReader(archivo_conceptos);
                String linea = br.readLine();
                while(linea != null){
                    conceptos_data.add(linea);
                    //Toast.makeText(this, "concepto: " + linea, Toast.LENGTH_SHORT).show();
                    linea = br.readLine();

                }
                br.close();
                archivo_conceptos.close();
                //Toast.makeText(this, "lectura correcta", Toast.LENGTH_SHORT).show();
            }
            catch(Exception ex){Toast.makeText(this, "error 3", Toast.LENGTH_SHORT).show();}

        }

        /*for(int i = 0; i < gastos_data.size(); i++){
            Toast.makeText(this, "dato: " + gastos_data.get(i), Toast.LENGTH_SHORT).show();
        }*/

        //se llenan objetos de gastos
        for(int i = 0; i < gastos_data.size(); i++){
            String linea = "";
            int dato = 0;

            int id_g = 0;
            String fecha_g = "";

            for(int j = 0; j < gastos_data.get(i).length(); j++){
                if(gastos_data.get(i).charAt(j) != ','){
                    linea += gastos_data.get(i).charAt(j);
                    //Toast.makeText(this, "linea: " + linea, Toast.LENGTH_SHORT).show();
                }
                else{
                    if(dato == 0)
                        id_g = Integer.parseInt(linea);

                    dato ++;
                    linea = "";
                }

                if(j == gastos_data.get(i).length()-1){
                    fecha_g = linea;
                }
            }
            gastos.add(new Gastos(id_g, fecha_g));
        }

        //se llenan objetos de depositos
        for(int i = 0; i < depositos_data.size(); i++){
            String linea = "";
            int dato = 0;

            int id_d = 0;
            float monto_d = 0;
            int id_gasto = 0;

            for(int j = 0; j < depositos_data.get(i).length(); j++){
                if(depositos_data.get(i).charAt(j) != ','){
                    linea += depositos_data.get(i).charAt(j);
                    //Toast.makeText(this, "linea: " + linea, Toast.LENGTH_SHORT).show();
                }
                else{
                    if(dato == 0)
                        id_d = Integer.parseInt(linea);
                    else if(dato == 1)
                        monto_d = Float.parseFloat(linea);

                    dato ++;
                    linea = "";
                }

                if(j == depositos_data.get(i).length()-1){
                    id_gasto = Integer.parseInt(linea);
                }
            }
            depositos.add(new Depositos(id_d, monto_d, id_gasto));
        }

        //se llenan objetos de depositos
        for(int i = 0; i < conceptos_data.size(); i++){
            String linea = "";
            int dato = 0;

            int id_c = 0;
            String nombre_c = "";
            float costo_c = 0;
            int id_gasto2 = 0;

            for(int j = 0; j < conceptos_data.get(i).length(); j++){
                if(conceptos_data.get(i).charAt(j) != ','){
                    linea += conceptos_data.get(i).charAt(j);
                    //Toast.makeText(this, "linea: " + linea, Toast.LENGTH_SHORT).show();
                }
                else{
                    if(dato == 0)
                        id_c = Integer.parseInt(linea);
                    else if(dato == 1)
                        nombre_c = linea;
                    else if(dato == 2)
                        costo_c = Float.parseFloat(linea);

                    dato ++;
                    linea = "";
                }

                if(j == conceptos_data.get(i).length()-1){
                    id_gasto2 = Integer.parseInt(linea);
                }
            }
            conceptos.add(new Conceptos(id_c, nombre_c, costo_c, id_gasto2));
        }
        total_gasto = 0;
        for(int i = 1; i < conceptos.size(); i++){
            //Toast.makeText(this, "Concepto: " + conceptos.get(i).getNombre(), Toast.LENGTH_SHORT).show();
            if(conceptos.get(i).getId_gasto() == gastos.get(gastos.size()-1).getId()){
                elementos.add("-" + conceptos.get(i).getNombre() + ": $" + conceptos.get(i).getCosto());
                total_gasto += conceptos.get(i).getCosto();
            }
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.lista_conceptos, elementos);
        listView.setAdapter(adapter);

        //Toast.makeText(this, "fecha: " + gastos.get(0).getFecha(), Toast.LENGTH_SHORT).show();

    }

    public void nuevo(View v){
        try{
            OutputStreamWriter archivo_gastos = new OutputStreamWriter(openFileOutput(txt1, Activity.MODE_PRIVATE));

            for(int i = 0; i < gastos.size(); i++)
                archivo_gastos.write("" + gastos.get(i).getId() + "," + gastos.get(i).getFecha() + "\n");

            archivo_gastos.write("" + gastos.get(gastos.size()-1).getId() + 1 + "," +
                    fecha.get(Calendar.DAY_OF_MONTH) + "_" + (fecha.get(Calendar.MONTH)+1) + "_" + fecha.get(Calendar.YEAR) + "\n");

            archivo_gastos.flush();
            archivo_gastos.close();

            OutputStreamWriter archivo_deposito = new OutputStreamWriter(openFileOutput(txt2, Activity.MODE_PRIVATE));

            for(int i = 0; i < depositos.size(); i++)
                archivo_deposito.write("" + depositos.get(i).getId() + "," + depositos.get(i).getMonto() + "," + depositos.get(i).getId_gasto() + "\n");

            archivo_deposito.write("" + depositos.get(depositos.size()-1).getId()+1 + "," +
                                             saldo_restante + "," +
                                             depositos.get(depositos.size()-1).getId_gasto()+1);

            archivo_deposito.flush();
            archivo_deposito.close();

            vaciar();
            LeerContenido();

            saldo_inicial = depositos.get(depositos.size()-1).getMonto();
            saldo_inicial_txt.setText("Saldo inicial: $"+saldo_inicial);
            total_gasto_txt.setText("Total gasto: $"+total_gasto);

            saldo_restante = saldo_inicial-total_gasto;
            saldo_restante_txt.setText("Saldo restante: $"+saldo_restante);
            //Toast.makeText(this, "Se creo gastos.txt", Toast.LENGTH_SHORT).show();
            //gastos_data.add("0," + fecha.get(Calendar.DAY_OF_MONTH) + "_" + (fecha.get(Calendar.MONTH)+1) + "_" + fecha.get(Calendar.YEAR));
        }
        catch(Exception ex){}
    }

    public void borrar_contenido(View v){
        try{

            OutputStreamWriter archivo_gastos = new OutputStreamWriter(openFileOutput(txt1, Activity.MODE_PRIVATE));
            archivo_gastos.write("0," + fecha.get(Calendar.DAY_OF_MONTH) + "_" + (fecha.get(Calendar.MONTH)+1) + "_" + fecha.get(Calendar.YEAR) + "\n");
            archivo_gastos.flush();
            archivo_gastos.close();

            OutputStreamWriter archivo_deposito = new OutputStreamWriter(openFileOutput(txt2, Activity.MODE_PRIVATE));
            archivo_deposito.write("0,0,0");
            archivo_deposito.flush();
            archivo_deposito.close();

            OutputStreamWriter archivo_conceptos = new OutputStreamWriter(openFileOutput(txt3, Activity.MODE_PRIVATE));
            archivo_conceptos.write("0,0,0,0");
            archivo_conceptos.flush();
            archivo_conceptos.close();

            Toast.makeText(this, "Se vació la informacion", Toast.LENGTH_SHORT).show();
        }
        catch(Exception ex){}

        vaciar();
        LeerContenido();

        saldo_inicial = depositos.get(depositos.size()-1).getMonto();
        saldo_inicial_txt.setText("Saldo inicial: $"+saldo_inicial);
        total_gasto_txt.setText("Total gasto: $"+total_gasto);

        saldo_restante = saldo_inicial-total_gasto;
        saldo_restante_txt.setText("Saldo restante: $"+saldo_restante);
    }

    private void vaciar(){
        gastos.clear();
        gastos_data.clear();
        depositos.clear();
        depositos_data.clear();
        conceptos.clear();
        conceptos_data.clear();
        elementos.clear();
    }
}

class Gastos{
    int id;
    String fecha;
    Gastos(int id, String fecha){
        this.id = id;
        this.fecha = fecha;
    }
    public int getId(){return id;}
    public String getFecha(){return fecha;}
}

class Depositos{
    int id, id_gasto;
    float monto;
    Depositos(int id, float monto, int id_gasto){
        this.id = id;
        this.monto = monto;
        this.id_gasto = id_gasto;
    }
    public int getId(){return id;}
    public float getMonto(){return monto;}
    public int getId_gasto(){return id_gasto;}
}

class Conceptos{
    int id, id_gasto;
    String nombre;
    float costo;

    Conceptos(int id, String nombre, float costo, int id_gasto){
        this.id = id;
        this.nombre = nombre;
        this.costo = costo;
        this.id_gasto = id_gasto;
    }
    public int getId(){return id;}
    public String getNombre(){return nombre;}
    public float getCosto(){return costo;}
    public int getId_gasto(){return id_gasto;}
}
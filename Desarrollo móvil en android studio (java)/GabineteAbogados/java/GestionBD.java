package com.example.armando.gabineteabogados;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class GestionBD extends SQLiteOpenHelper {

    String tabla_abogados = "create table ABOGADOS (id INTEGER primary key," +
                                                   "nombre TEXT," +
                                                   "telefono TEXT)";

    String tabla_asuntos = "create table ASUNTOS (no_exp INTEGER primary key, " +
                                                 "fecha_inicio TEXT," +
                                                 "fecha_fin TEXT," +
                                                 "estado TEXT," +
                                                 "abogado INTEGER references ABOGADOS(id)," +
                                                 "cliente INTEGER references CLIENTES(id))";

                                                 //"id_cliente int references CLIENTES(id)," +
                                                 //"id_abogado int references ABOGADOS(id))";

    String tabla_clientes = "create table CLIENTES (id INTEGER primary key," +
                                                   "nombre TEXT," +
                                                   "dni TEXT," +
                                                   "direccion TEXT)";

    public GestionBD(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase dataBase) {
        dataBase.execSQL(tabla_abogados);
        dataBase.execSQL(tabla_clientes);
        dataBase.execSQL(tabla_asuntos);


    }

    @Override
    public void onOpen(SQLiteDatabase dataBase) {
        super.onOpen(dataBase);
        if (!dataBase.isReadOnly()) {
            // Enable foreign key constraints
            dataBase.execSQL("PRAGMA foreign_keys=ON;");
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase dataBase, int i, int i1) {

        dataBase.execSQL("drop table if exists ASUNTOS");
        dataBase.execSQL("drop table if exists ABOGADOS");
        dataBase.execSQL("drop table if exists CLIENTES");

        dataBase.execSQL(tabla_abogados);
        dataBase.execSQL(tabla_asuntos);
        dataBase.execSQL(tabla_clientes);

    }
}

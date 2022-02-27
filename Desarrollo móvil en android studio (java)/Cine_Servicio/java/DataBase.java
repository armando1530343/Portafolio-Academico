package com.example.vannessa.cine_servicio;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DataBase extends SQLiteOpenHelper {
    String cines = "create table cines (id INTEGER primary key," +
            "nombre TEXT," +
            "calle TEXT," +
            "numero TEXT," +
            "telefono TEXT," +
            "precio1 int," +
            "precio2 int," +
            "precio3 int," +
            "precio4 int)";

    String peliculas = "create table peliculas (id INTEGER primary key, " +
            "titulo TEXT," +
            "horario TEXT," +
            "director TEXT," +
            "protagonistas TEXT," +
            "genero TEXT," +
            "clasificacion TEXT," +
            "cine INTEGER references cines(id))";


    public DataBase(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase dataBase) {
        dataBase.execSQL(cines);
        dataBase.execSQL(peliculas);

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

        dataBase.execSQL("drop table if exists cines");
        dataBase.execSQL("drop table if exists peliculas");
        dataBase.execSQL(cines);
        dataBase.execSQL(peliculas);
    }
}

package com.example.armando.buscador;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class SQLite extends SQLiteOpenHelper {

    String tabla1 = "create table tabla1 (id INTEGER primary key," +
                                          "nombre TEXT," +
                                          "telefono TEXT)";

    String tabla2 = "create table tabla2 (id INTEGER primary key," +
                                         "nombre TEXT," +
                                         "edad INTEGER)";

    public SQLite(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase dataBase) {
        dataBase.execSQL(tabla1);
        dataBase.execSQL(tabla2);

    }

    @Override
    public void onOpen(SQLiteDatabase dataBase) {
        super.onOpen(dataBase);
        if (!dataBase.isReadOnly()) {
            // Enable foreign key constraints
            //dataBase.execSQL("PRAGMA foreign_keys=ON;");
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase dataBase, int i, int i1) {

        dataBase.execSQL("drop table if exists tabla1");
        dataBase.execSQL("drop table if exists tabla2");
        dataBase.execSQL(tabla1);
        dataBase.execSQL(tabla2);
    }
}

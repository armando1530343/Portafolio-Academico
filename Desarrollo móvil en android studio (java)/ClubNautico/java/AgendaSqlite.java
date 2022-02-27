package com.example.victoria.club_nautico;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

public class AgendaSqlite extends SQLiteOpenHelper{
    String persona   = "CREATE TABLE Persona (matricula INTEGER PRIMARY KEY, nombre TEXT, relacion TEXT)";
    String barco  = "CREATE TABLE Barco (num INTEGER PRIMARY KEY, cuota INTEGER, " +
            "propietario REFERENCES Persona(matricula))";
    String salidas = "CREATE TABLE Salidas (id INTEGER PRIMARY KEY, fecha_salida TEXT, hora_salida TEXT, " +
            "destino TEXT, barco REFERENCES Barco(num), patron REFERENCES Persona(matricula) )";

    public AgendaSqlite(Context context, String name, CursorFactory factory,int version) {
        super(context, name, factory, version);

    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        //Se ejecuta la sentencia SQL de creaci�n de la tabla
        db.execSQL(persona);
        db.execSQL(barco);
        db.execSQL(salidas);
    }

    @Override
    public void onOpen(SQLiteDatabase db) {
        super.onOpen(db);
        if (!db.isReadOnly()) {
            // Enable foreign key constraints
            db.execSQL("PRAGMA foreign_keys=ON;");
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        //eliminamos la version anterior de la tabla
        db.execSQL("DROP TABLE IF EXISTS Persona");
        db.execSQL("DROP TABLE IF EXISTS Barco");
        db.execSQL("DROP TABLE IF EXISTS Salidas");

        //aqu� creamos la nueva versi�n de la tabla
        db.execSQL(persona);
        db.execSQL(barco);
        db.execSQL(salidas);

    }
}

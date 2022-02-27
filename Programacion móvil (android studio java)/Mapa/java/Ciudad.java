package com.example.armando.mapa;

import java.util.ArrayList;

public class Ciudad {

    private String nombre;
    private ArrayList<Integer> distancias;

    public Ciudad(){
        distancias = new ArrayList<Integer>();
    }

    public void addDistancia(int i, int n){
        distancias.add(i, n);
    }
    public void setDistancia(int i, int n){
        distancias.set(i, n);
    }

    public ArrayList<Integer> getDistancias(){
        return distancias;
    }

    public String getNombre(){
        return nombre;
    }

    public void setNombre(String nombre){
        this.nombre = nombre;
    }
}

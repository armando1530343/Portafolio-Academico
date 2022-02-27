/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;
import java.util.ArrayList;

/**
 *
 * @author Armando Isaac
 */
public class WatherData implements Subjet{
    private ArrayList<Observer> observers; 
    private float temperature;
    private float humidity;
    private float pression;

    public WatherData() {
        observers = new ArrayList<>();
    }
    
    @Override
    public void registarObserver(Observer o){
        
    }
    
    @Override
    public void removeObserver(Observer o){
        int i = observers.indexOf(o);
        if(i>=1){}
    }
    
    @Override
    public void notifyObserver(){
        
    }   
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;
import java.util.Observable;
import java.util.Observer;
public class ForecastDisplay implements Observer, DisplayElement {
    
    private float currentPressure = 29.2f;
    private float lastPressure;
    private WheatherData weatherData;
    
    
    public ForecastDisplay(WheatherData  weatherData){
        this.weatherData=weatherData;
        weatherData.addObserver(this);
    }
    
    public void update(Observable obs,Object arg){
        if(obs instanceof WheatherData){
            WheatherData wd =(WheatherData)obs;
            lastPressure = currentPressure;
            currentPressure=wd.getPressure();
            display();
        }
    }
    
    public void display(){
        if(currentPressure > lastPressure){
            System.out.println("Forecast: Improving weather on the way!");
        }else if(currentPressure ==lastPressure){
            System.out.println("Forecast:More of the same.");
        }else if(currentPressure < lastPressure){
            System.out.println("Forecast:Watch out for cooler, rainy weatherq");
        }
    }
}


package edu.upv.poo;
import java.util.Observable;
import java.util.Observer;
public class StatisticsDisplay implements Observer, 

DisplayElement {
    private float currentTemp=30.0f;
    private float lastTemperature;
    
    private float promedio;
    private WheatherData weatherData;
    
    public StatisticsDisplay(WheatherData  weatherData){
        this.weatherData=weatherData;
        weatherData.addObserver(this);
    }
    
    public void update(Observable obs,Object arg){
        if(obs instanceof WheatherData){
            WheatherData wd =(WheatherData)obs;
            lastTemperature = currentTemp;
            currentTemp=wd.getTemperature();
            display();
        }
    }
    
    
     
    @Override
     public void display(){
         if(currentTemp > lastTemperature){
             System.out.printf("Temperatura Maxima: %f\n",this.currentTemp);
         }else if(currentTemp < lastTemperature){
             System.out.printf("Temperatura Minima: %f\n",this.currentTemp);
         }else if(currentTemp > 28 &&currentTemp < 34 ){
             System.out.printf("promedio: %f\n",this.currentTemp);
         }
     
         
    }
    
    
    
}

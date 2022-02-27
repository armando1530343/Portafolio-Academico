
package edu.upv.poo;
import java.util.Observer;
import java.util.Observable;
public class CurrentConditionsDisplay implements Observer, DisplayElement{
    
    private Observable observable;
    private float temperature;
    private float humidity;
    
    
    public CurrentConditionsDisplay(Observable observable){
        this.observable=observable;
        observable.addObserver(this);
    }
    
    @Override
    public void update(Observable obs, Object arg){
        if(obs instanceof WheatherData){
            WheatherData wd =(WheatherData)obs;
            this.temperature=wd.getTemperature();
            this.humidity=wd.getHumidity();
            display();
        
        }
    }
    
    public void display(){
        System.out.printf("Current conditions:%f °C degrees and %f %% humadity\n",this.temperature,this.humidity);
    }
    
    
}

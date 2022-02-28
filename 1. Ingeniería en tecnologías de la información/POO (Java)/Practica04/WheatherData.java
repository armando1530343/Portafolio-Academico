
package edu.upv.poo;
import java.util.Observable;

public class WheatherData extends Observable{
    
    private float temperature;
    private float humidity;
    private float pressure;
    
    
    public void setMeasurement(float temperature, float humidity,float pressure){
        this.temperature=temperature;
        this.humidity=humidity;
        this.pressure=pressure;
        this.measurementsChanged();
    }
    
    public void measurementsChanged(){
        setChanged();
        notifyObservers();
    }
    /**
     * @return the temperature
     */
    public float getTemperature() {
        return temperature;
    }

    /**
     * @return the humidity
     */
    public float getHumidity() {
        return humidity;
    }

    /**
     * @return the pressure
     */
    public float getPressure() {
        return pressure;
    }
    
}

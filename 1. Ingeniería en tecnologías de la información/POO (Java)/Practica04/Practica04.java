
package edu.upv.poo;

public class Practica04 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        WheatherData weatherData =new WheatherData();
        
        CurrentConditionsDisplay currentConditions= new CurrentConditionsDisplay(weatherData);
        ForecastDisplay forecast = new ForecastDisplay(weatherData);
        StatisticsDisplay s = new StatisticsDisplay(weatherData);
        
        /*
        * Hacer la implementacion de la clase StatisticsDisplay.
        * Tinene que desplegar las temp minima y maximas y promedio
        */
        
        // simulacion de cambio en objetop observable
        weatherData.setMeasurement(30.0f,65.0f,30.4f);
        weatherData.setMeasurement(34.0f,70.0f,29.2f);
        weatherData.setMeasurement(28.0f,90.5f,29.2f);
        
    }
    
}

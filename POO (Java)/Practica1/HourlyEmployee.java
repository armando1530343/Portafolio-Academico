/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

/**
 *
 * @author Armando Isaac
 */
public class HourlyEmployee extends Empleado{

    private double wage;
    private double hours;

    public HourlyEmployee(String firstname, String lastname, String ssn, double wage, double hours) {
        super(firstname, lastname, ssn);
        this.wage = wage;
        this.hours = hours;
        setWage(wage);
        setHours(hours);
    }

    public double getWage() {
        return wage;
    }

    public final void setWage(double wage) {
        this.wage = wage < 0.0 ? 0.0 : wage;
    }
    
    public double getHours() {
        return hours;
    }

    public final void setHours(double hours) {
        if(hours < 0.0)
            this.hours = 0.0;
        else if(hours > 168.0)
            this.hours = 168.0;
        else
            this.hours = hours;
    }
    
    @Override
    public String toString() {
        return String.format(
                "%s \n [Hourly Employee] Wage: $%,.2f Hours: $%,.2f", 
                super.toString(), getWage(), getHours());
    }
    
    @Override
    public double earnings() {
        if(getHours() <= 40.0)
            return getHours() * getHours();
        else
            return 40.0 * getHours() + (getHours() - 40.0) * getWage() * 1.5;
    }
    
}

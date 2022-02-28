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
public class BasePlusHourlyEmployee extends HourlyEmployee{
    private double base;

    public BasePlusHourlyEmployee(double base, String firstname, String lastname, String ssn, double wage, double hours) {
        super(firstname, lastname, ssn, wage, hours);
        //this.base = base;
        setBase(base);
    }

    public double getBase() {
        return base;
    }

    public final void setBase(double base) {
        this.base = base < 0.0 ? 0.0 : base;
    }
    
    @Override
    public double earnings(){
        return super.earnings() + base;
    }
    @Override
    public String toString() {
        return String.format(
                "%s \n [BasePlusHourlyEmployee] Base: $%,.2f", 
                super.toString(), getBase());
    }
    
    
}

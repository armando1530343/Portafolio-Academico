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
public class SalariedEmployee extends Empleado{

    private double weeklySalary;
    public SalariedEmployee(String firstname, String lastname, String ssn, double weeklySalary) {
        super(firstname, lastname, ssn);
        setWeeklySalary(weeklySalary);
    }

    public double getWeeklySalary() {
        return weeklySalary;
    }

    public final void setWeeklySalary(double weeklySalary) {
        this.weeklySalary = weeklySalary < 0.0 ? 0.0 : weeklySalary;
    }

    @Override
    public double earnings() {
        return getWeeklySalary();
    }
    
    @Override
    public String toString() {
        return String.format(
                "%s \n [Salary Employee] WeeklySalary: $%,.2f", super.toString(), getWeeklySalary());
    }   
}

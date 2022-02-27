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
public class BonoPlusSalariedEmployee extends SalariedEmployee{
    private double bono;

    public BonoPlusSalariedEmployee(String firstname, String lastname, String ssn, double weeklySalary, double bono) {
        super(firstname, lastname, ssn, weeklySalary);
        this.bono = bono;
    }

    public double getBono() {
        return bono;
    }

    public final void setBono(double bono) {
        this.bono = bono < 0.0 ? 0.0 : bono;
    }
    
    @Override
    public double earnings(){
        return super.earnings() + bono;
    }
    
    @Override
    public String toString() {
        return String.format(
                "%s \n [BonoPlusSalariedEmployee] Bono: $%,.2f", super.toString(), getBono());
    }    
}
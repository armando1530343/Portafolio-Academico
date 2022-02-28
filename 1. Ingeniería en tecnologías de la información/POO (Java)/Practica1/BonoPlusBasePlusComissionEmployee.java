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
public class BonoPlusBasePlusComissionEmployee  extends BasePlusComissionEmployee{
    private double bono;

    public BonoPlusBasePlusComissionEmployee(
            String firstname, String lastname, String ssn, double grossSales, 
            double comissionRate, double bono, double base) {
        super(base, firstname, lastname, ssn, grossSales, comissionRate);
        this.bono = bono;
        setBono(bono);
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
                "%s \n [BonoPlusBasePlusComissionEmployee] Bono: $%,.2f", 
                super.toString(), getBono());
    }
}
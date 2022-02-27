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
public class ComissionEmployee extends Empleado{
    private double grossSales;
    private double comissionRate;

    public ComissionEmployee(
            String firstname, String lastname, String ssn, double grossSales, double comissionRate) {
        super(firstname, lastname, ssn);
        this.grossSales = grossSales;
        this.comissionRate = comissionRate;
    }

    public double getGrossSales() {
        return grossSales;
    }

    public final void setGrossSales(double grossSales) {
        this.grossSales = grossSales < 0.0 ? 0.0 : grossSales;
    }

    public double getComissionRate() {
        return comissionRate;
    }

    public final void setComissionRate(double comissionRate) {
        if(comissionRate < 0.0)
            this.comissionRate = 0.0;
        else if(comissionRate > 1.0)
            this.comissionRate = 1.0;
        else
            this.comissionRate = comissionRate;
    }   
    
    @Override
    public double earnings(){
        return getGrossSales() * getComissionRate();
    }
    @Override
    public String toString() {
        return String.format(
                "%s \n [Comission Employee] GrossSales: $%,.2f ComissionRate: %,.2f%%", 
                super.toString(), getGrossSales(), getComissionRate() * 100.0);
    }
    
}
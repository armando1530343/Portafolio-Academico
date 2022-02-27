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
public class BasePlusComissionEmployee extends ComissionEmployee{
    private double base;

    public BasePlusComissionEmployee(double base, String firstname, String lastname, String ssn, double grossSales, double comissionRate) {
        super(firstname, lastname, ssn, grossSales, comissionRate);
        this.base = base;
        setBase(base);
    }
    public final void setBase(double base){
        this.base = base < 0.0 ? 0.0 : base;
    }
     public double getBase(){
         return base;
     }
     @Override
     public double earnings(){
         return super.earnings() + base;
     }
     
     @Override
    public String toString() {
        return String.format(
                "%s \n [BasePlusComissionEmployee] Base: $%,.2f", 
                super.toString(), getBase());
    }
}

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
public class Practica1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
                
        /*Empleado salariedE = new SalariedEmployee(
                "Empleado Nombre", "Empleado Apellido", "dfsdfdsgt", 5034.12);*/
        Empleado salariedBonus = new BonoPlusSalariedEmployee(
                "Empleado Nombre", "Empleado Apellido", "dfsdfdsgt", 5034.12, 50.0);
        
        Empleado hourlyE = new BonoPlusBasePlusHourlyEmployee(
                "Employee", "Hourly", "shduehdgf", 434.3, 34.1, 40.0, 30.5);
        Object comissionE = new BonoPlusBasePlusComissionEmployee(
                "Employee", "Comission lastname", "asd234432", 34234.21, 0.25, 85.4, 25.0);
        
        //-----Casting-----
        ((ComissionEmployee)comissionE).setGrossSales(354776.43);        
        ComissionEmployee comissionE_copy = (ComissionEmployee) comissionE;
        comissionE_copy.setComissionRate(0.3465);
        //------------------
        
        Empleado[] employees = new Empleado[3];
        employees[0] = salariedBonus;
        employees[1] = hourlyE;
        employees[2] = (Empleado)comissionE;
        
        polymorphicalProcessingEarning(employees);
        
    
    }
    public static void polymorphicalProcessingEarning(Empleado[] employees){
        
        System.out.println("========================");
        
        for(Empleado e : employees){
            System.out.println(e);
            System.out.printf(" EARNINGS: $%,.2f\n", e.earnings());
        }
        
        System.out.println("========================");
    }    
}

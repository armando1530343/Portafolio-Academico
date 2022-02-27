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
public class Employee {
    private String firstname;
    private String lastname;
    private String ssn;
    private double salary;

    public Employee(String firstname, String lastname, String ssn, double salary) {
        this.firstname = firstname;
        this.lastname = lastname;
        this.ssn = ssn;
        this.salary = salary;
    }

    public String getFirstname() {
        return firstname;
    }

    public String getLastname() {
        return lastname;
    }

    public String getSsn() {
        return ssn;
    }
    public double getSalary(){
        return salary;
    }
    
    @Override
    public String toString(){
        return String.format("%s %s ISBN: %s", getFirstname(), getLastname(), getSsn());
    }
   
}

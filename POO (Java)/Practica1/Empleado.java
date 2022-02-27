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
public abstract class Empleado {
    private String firstname;
    private String lastname;
    private String ssn;

    public Empleado(String firstname, String lastname, String ssn) {
        this.firstname = firstname;
        this.lastname = lastname;
        this.ssn = ssn;
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
    
    @Override
    public String toString(){
        return String.format("%s %s ISBN: %s", getFirstname(), getLastname(), getSsn());
    }
    
    public abstract double earnings();
}
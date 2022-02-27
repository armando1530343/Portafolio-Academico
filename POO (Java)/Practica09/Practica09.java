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
import java.sql.*;
public class Practica09 {
    
    final static String connectionStr = "jdbc:mysql://localhost:3307/escuela2?user=root&password=";
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws SQLException{
        // TODO code application logic here
        Connection conn = null;
        conn = DriverManager.getConnection(connectionStr);
        
        /*Statement stmt = conn.createStatement();
        stmt.execute("Select * from alumnos");
        ResultSet r = stmt.getResultSet();*/
        
    }
    
    
    
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;
import java.util.Arrays;
import java.util.function.*;
import java.util.stream.*;
import static java.lang.System.out;
import java.util.Comparator;
import java.util.Scanner;
import edu.upv.poo.lib.TestClass;
/**
 *
 * @author Armando Isaac
 */
public class Practica11 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner in = new Scanner(System.in);
        
        TestClass test = new TestClass();
        test.test("armando");
        
        out.println("Ingrese longitud del Array: ");
        int arrayLen = in.nextInt();
        in.nextLine();
        
        double[] myDoubleArray = new double [arrayLen];
        for(int i = 0; i < arrayLen; i++){
            out.printf("[%d] = ", i);
            myDoubleArray[i] = in.nextDouble();
            in.nextLine();
        }
        
        DoubleStream.of(myDoubleArray).forEach(i -> out.println(i));
        
        DoubleConsumer imprimirNum1 = (double i) -> out.println(i);
        DoubleStream.of(myDoubleArray).forEach(imprimirNum1);
        
        DoubleConsumer imprimirNum2 = (i) -> out.println(i);
        DoubleStream.of(myDoubleArray).forEach(imprimirNum2);
        
        DoubleConsumer imprimirNum3 = i -> out.println(i);
        DoubleStream.of(myDoubleArray).forEach(imprimirNum3);
        
        DoubleConsumer imprimirNum4 = i -> {
            out.println(i);
        };
        DoubleStream.of(myDoubleArray).forEach(imprimirNum4);
        
        out.println("pares");
        DoubleStream.of(myDoubleArray)
                .filter(i -> i % 2 == 0)
                .forEach(i -> out.println(i));
        
        DoublePredicate impares = v->v%2!=0;
        DoubleConsumer imprimir = v->out.println(v);
        out.println("Impares: ");
        DoubleStream.of(myDoubleArray)
                .filter(impares).forEach(imprimir);
        
        Employee[] employees = {
            new Employee("Jason", "Red", "RJ001", 1252.43),
            new Employee("Ashley", "Green", "GA001", 23423.43),
            new Employee("Matthew", "brown", "BM002", 1231.43),
            new Employee("Juan", "brown", "BJ002", 3453.43),
            new Employee("Jason", "Red", "RJ001", 45645.43),
            new Employee("Ashley", "Green", "GA001", 23423.43),
            new Employee("Matthew", "brown", "BM002", 1232.43),
            new Employee("Juan", "brown", "BJ002", 9987.43),
            new Employee("Jason", "Red", "RJ001", 782364.43),
            new Employee("Ashley", "Green", "GA001", 7346.43),
            new Employee("Matthew", "brown", "BM002", 5253.43),
            new Employee("Juan", "brown", "BJ002", 74635.43)
        };
        Stream.of(employees)
                .filter(e -> e.getSalary() > 5000.0)
                .forEach(e -> out.println(e));
        Stream.of(employees)
                .sorted(Comparator.comparing(Employee::getSalary))
                .forEach(e -> out.println(e + " Salary: " + e.getSalary()));
        Predicate<Employee> salaryB5000T10000 =
                e -> e.getSalary() >= 5000 && e.getSalary() <= 10000;
        
        out.println("Salary >= 5000 and <= 10000");
        
        Stream.of(employees)
                .filter(salaryB5000T10000)
                .forEach(e -> out.println(e + " Salary: " + e.getSalary()));
        out.println("Rich:");
        Employee[] richEmployee =
            Stream.of(employees)
                .filter(e -> e.getSalary() > 50000.0)
                .collect(Collectors.toList())
                .toArray(new Employee[0]);
        for(Employee e : richEmployee){
            out.println(e);
        }
       
    }   
}
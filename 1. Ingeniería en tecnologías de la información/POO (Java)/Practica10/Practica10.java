/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.*;
import java.nio.*;
import static java.lang.System.out;
import org.json.simple.*;
import org.json.simple.parser.*;
import java.net.*;

/**
 *
 * @author Armando Isaac
 */
public class Practica10 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)throws Exception {
        // TODO code application logic here
        String rutaArchivo = "C:\\Users\\Armando Isaac\\Desktop\\POO\\Practica10\\src\\edu\\upv\\poo\\MyJasonFile.json";
        String textoJson = readFile(rutaArchivo);
        out.println(textoJson);
        
        
        out.println(textoJson);         
        JSONObject myJson = (JSONObject)new JSONParser().parse(textoJson);        
        int id = Integer.parseInt(myJson.get("Id").toString());
        out.println("Id: " + id);        
        String matricula = (String)myJson.get("matricula");
        out.println("Matricula: " + matricula);
        out.printf("Nombre: %s\n",myJson.get("nombre"));
        out.printf("Apellido Paterno: %s\n",myJson.get("apellidoPaterno"));
        out.printf("Apellido Materno: %s\n",myJson.get("apellidoMaterno"));
        JSONObject carrera = (JSONObject)myJson.get("carrera");
        out.printf("Nombre: %s \n", carrera.get("nombre"));        
        JSONArray materiasCursadas = (JSONArray)myJson.get("materiasCursadas");
        out.println("Materias Cursadas");
        for(Object materia : materiasCursadas){
            out.printf("- %s\n", materia);
        }        
        JSONArray calificaciones = (JSONArray)myJson.get("calificaciones");
        for(Object calif : calificaciones){
            JSONObject calJson = (JSONObject)calif;
            out.println("Materia " + calJson.get("materia"));
            int cal = Integer.parseInt(calJson.get("calificacion").toString());
            out.printf(" %d ->%s\n", cal, cal>=70?"Pasó":"No paso");
        }
        
        String ruta1 = "http://200.57.172.35/api/General/Catalogos.svc/json/ConsultarEstados?AppKey=C14F15A3028F4C57A06874ABAD818366";
        String estados = readFile(ruta1);
        String ruta2 = "http://200.57.172.35/api/General/Catalogos.svc/json/ConsultarMunicipios?AppKey=C14F15A3028F4C57A06874ABAD818366&Estado";
        String municipios = readFile(ruta2);
        out.println(municipios);
        
        JSONObject JEstados = (JSONObject)new JSONParser().parse(estados);
        JSONObject JMunicipios = (JSONObject)new JSONParser().parse(municipios);
        
        JSONObject de = (JSONObject)JEstados.get("d");        
        JSONArray est = (JSONArray)de.get("Estados");
        
        JSONObject dm = (JSONObject)JMunicipios.get("d");        
        JSONArray mun = (JSONArray)dm.get("Municipios");
        
        for(Object m : mun){
            JSONObject mJson = (JSONObject)m;
            JSONObject eJson = (JSONObject)mJson.get("Estado");
            out.println("Estado: " + eJson.get("Nombre") + "  Municipio:" + mJson.get("Nombre"));            
        }
        
    }
    public static String readFile(String file)throws IOException{
        String typeFile = ""+file.charAt(0)+file.charAt(1)+file.charAt(2)+file.charAt(3);
        String contenido = "";        
        if(!typeFile.equals("http")){
            java.util.List<String> lines = Files.lines(Paths.get(file)).collect(java.util.stream.Collectors.toList());
            for(String l : lines){
                contenido += l +"\n";
            }
        }
        else{
            URL url = new URL(file);
            URLConnection conn = (URLConnection) url.openConnection();
            BufferedReader rd = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            String line;
            while ((line = rd.readLine()) != null) {
               contenido += line;
            }
            rd.close();
        }        
        
        return contenido;
    }  
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package conecta4;

/**
 *
 * @author Armando Isaac
 */
public class Tablero {
    int f;//numero de filas del tablero
    int c;//numero de columnas del tablero
    int []tope;//ultimo valor de cada columna del tablero
    int [][]tabla;//tablero
    Tablero(int fi, int co){
        //a las variables de la clase se le asignan los valores de los parametros
        f=fi;
        c=co;
        tope = new int [c];//se crea un vector con la cantidad de columnas
        tabla = new int [f][c];//se crea la matriz del tablero
        int i, j;//variables iteradoras
    
        //este ciclo llena el tablero de ceros desde el inicio
        for(i=0;i<f;i++){
            for(j=0;j<c;j++){
                tabla[i][j]=0;
            }
        }
        //este almacena el numero de espacios disponibles de cada columna
        for(i=0;i<c;i++)
            tope[i]=f-1;
    }
    
    //despliega los valores del tablero
    public void mostrar(){
        int i, j;
        for(i=0;i<f;i++){
            for(j=0;j<c;j++){
                System.out.print(tabla[i][j]+" ");
            }
            System.out.println();
        }
    }
    
    //esta funcion inserta en la columna que se indica y devuelve un valor boleano
    //indicando si el juego termina ó continua
    public boolean inserta(int col, int ficha){
        int i=0, a, b; 
        col--;//esta variable decrementa porque la funcion acepta valores mayores a 0
        //pero las columnas del tablero comienzan en el indice 0
            
            //ciclo que verifica todas las posibles formas de ganar en el juego
            //que regresan un true en caso de que alguna condicion se cumpla y esto hará que termine el juego
            do{
                if(i==tope[col] && tabla[i][col]==0){
                    tabla[i][col]=ficha;                  
                                
                    if(i<f-1 && col<c-1){
                        if(tabla[i][col]==tabla[i][col+1] && tabla[i][col]==tabla[i+1][col+1] && tabla[i][col]==tabla[i+1][col])
                            return true;
                    }
                    if(i<f-1 && col<c-1 && col>0){
                        if(tabla[i][col]==tabla[i][col-1] && tabla[i][col]==tabla[i+1][col-1] && tabla[i][col]==tabla[i+1][col])
                            return true;
                    }
                    if(i<=f-4){
                        if(tabla[i][col]==tabla[i+1][col] && tabla[i][col]==tabla[i+2][col] && tabla[i+3][col]==tabla[i][col])
                            return true;
                    }
                    if(col<=c-4){
                        if(tabla[i][col]==tabla[i][col+1] && tabla[i][col]==tabla[i][col+2] && tabla[i][col]==tabla[i][col+3])
                            return true;
                    }
                    if(col>=3){
                        if(tabla[i][col]==tabla[i][col-1] && tabla[i][col]==tabla[i][col-2] && tabla[i][col]==tabla[i][col-3])
                            return true;
                    }
                    if(col>=2){
                        if(tabla[i][col]==tabla[i][col-1] && tabla[i][col]==tabla[i][col-2] && tabla[i][col]==tabla[i][col+1])
                            return true;
                    }
                    if(col>=1){
                        if(tabla[i][col]==tabla[i][col-1] && tabla[i][col]==tabla[i][col+1] && tabla[i][col]==tabla[i][col+2])
                            return true;
                    }
                    if(i<=f-4 && col<=c-4){
                        if(tabla[i][col]==tabla[i+1][col+1] && tabla[i][col]==tabla[i+2][col+2] && tabla[i][col]==tabla[i+3][col+3])
                            return true;
                    }
                    if(i<=f-4 && col>=3){
                        if(tabla[i][col]==tabla[i+1][col-1] && tabla[i][col]==tabla[i+2][col-2] && tabla[i][col]==tabla[i+3][col-3])
                            return true;
                    }                   
                    tope[col]--;
                    break;
                }
                i++;
            }
            while(true);
        
        return false;//en caso de que ninguna condicion se cumpla, el juego continúa
    }
}
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Estructura {

	int repeticiones;
	string nombre;

	public Estructura(int repeticiones, string nombre){
		this.repeticiones = repeticiones;
		this.nombre = nombre;
	}

	public string getNombre() { return nombre; }

	public int getRepeticiones() { return repeticiones; }
	public void setRepeticiones(int r) { repeticiones = r; }
    
 
}

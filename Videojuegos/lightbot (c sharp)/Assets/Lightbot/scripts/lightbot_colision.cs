using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lightbot_colision : MonoBehaviour {

	string nombre_colision;

	void OnCollisionEnter(Collision collision)
    {      
		//se obtiene el nombre del objeto que colisiona
		nombre_colision = collision.gameObject.name;
        
    }

	public string getColision(){
		return nombre_colision;
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bloque : MonoBehaviour {

	//public bool caminar;
	public bool salta_norte, salta_sur, salta_este, salta_oeste;
	public bool foco;
	public bool camina_norte, camina_sur, camina_este, camina_oeste;


	// Use this for initialization
	void Start () {
		this.GetComponent<Renderer>().material.color = foco ? Color.blue : Color.gray;
	}

}

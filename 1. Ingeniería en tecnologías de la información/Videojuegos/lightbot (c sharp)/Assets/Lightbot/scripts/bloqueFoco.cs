using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bloqueFoco : MonoBehaviour {


	public bool caminar;
    public bool saltar;

	// Use this for initialization
	void Start () {
		this.GetComponent<Renderer> ().material.color = Color.blue;
	}

	public bool getCaminar() { return caminar; }
    public bool getSaltar() { return saltar; }
}

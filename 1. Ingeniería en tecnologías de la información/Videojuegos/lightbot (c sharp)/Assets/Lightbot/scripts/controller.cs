using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class controller : MonoBehaviour {

	Rigidbody rb;
	public float fuerzaSalto = 50f;
	private int touches = 0;
	private Animator animator;
	private bool salto;

	GameObject cubo;
	Renderer render;
	// Use this for initialization
	void Start () {
		rb = GetComponent<Rigidbody> ();
		animator = GetComponent<Animator> ();
		salto = false;
		cubo = GetComponent<GameObject> ();
		render = GetComponent<Renderer> ();
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetMouseButtonDown(0)){
			//rb.AddForce (new Vector3 (0,fuerzaSalto,0));
			//touches++;
			//salto = !salto;
			//animator.SetBool ("salto", salto);

			/*if (touches == 1) {
				animator.SetBool ("salto", true);
			} 
			else {
				animator.SetBool ("salto", false);
			}*/
		}

	}

	void OnCollisionEnter(Collision collision){
		//render.material.color = Color.blue;
		//Debug.Log(collision.gameObject.name);
	}
}

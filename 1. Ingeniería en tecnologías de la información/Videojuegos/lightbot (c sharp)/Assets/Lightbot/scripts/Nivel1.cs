using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Nivel1 : MonoBehaviour {

	List<Estructura> acciones_main;
	GameObject lightbot;
	//posiciones iniciales Lightbot
	static float X = 0, Y = 1.5f, Z = 6;

	Animator animator;
	float posX, posY, posZ;
	float nuevoX, nuevoY, nuevoZ;
	int rotacion;
	int total_movimientos = 0;

	List<float> timer_accion;

	float time = 0.0f;
	float time2 = 0.0f;
	int tiempo = 0;

	bool obtener_posicion = false;
	bool start = false;

	int n = 0;

	// Use this for initialization
    void Start()
    {
		lightbot = GameObject.Find("lightbot");
		animator = lightbot.GetComponent<Animator>();
    }

	public void setDatos(List<Estructura> datos){

		acciones_main = datos;

		timer_accion = new List<float>();
		n = 0;
		total_movimientos = 0;

		for (int i = 0; i < acciones_main.Count; i++){
			Debug.Log(acciones_main[i].getNombre());
			total_movimientos += acciones_main[i].getRepeticiones();
			for (int j = 0; j < acciones_main[i].getRepeticiones();j++){
				timer_accion.Add(0);
			}

		}

		start = true;

		Ejecutar();
	}

	bool activo = true;
     
	private void Ejecutar(){
		for (int i = 0; i < acciones_main.Count; i++)
        {
            for (int j = 0; j < acciones_main[i].getRepeticiones(); j++)
            {

				if (acciones_main[i].getNombre().Contains("f_caminar"))
				{
					
					StartCoroutine(caminar(n + 1.5f));
				}
				else if (acciones_main[i].getNombre().Contains("f_iluminar"))
				{
					StartCoroutine(foco(n + 1.5f));
				}
				else if (acciones_main[i].getNombre().Contains("f_saltar"))
                {
					StartCoroutine(saltar(n + 1.5f));
                }
                n++;
            }
        }
	}

	private IEnumerator caminar(float t){
		yield return new WaitForSeconds(t);
  
		posX = lightbot.GetComponent<Transform>().localPosition.x;
        posY = lightbot.GetComponent<Transform>().localPosition.y;
		posZ = lightbot.GetComponent<Transform>().localPosition.z;

		rotacion = Mathf.FloorToInt(lightbot.GetComponent<Transform>().localRotation.y);

		Debug.Log("rotacion: " + rotacion);
		if(rotacion >= -1 && rotacion <= 1){


			animator.Play("camina2");
			lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ - 3);
            
            
		}

	}  
	private IEnumerator saltar(float t){
        yield return new WaitForSeconds(t);
  
        posX = lightbot.GetComponent<Transform>().localPosition.x;
        posY = lightbot.GetComponent<Transform>().localPosition.y;
        posZ = lightbot.GetComponent<Transform>().localPosition.z;

        rotacion = Mathf.FloorToInt(lightbot.GetComponent<Transform>().localRotation.y);

        Debug.Log("rotacion: " + rotacion);
        if(rotacion >= -1 && rotacion <= 1){


            animator.Play("foco");
            lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ - 3);
            
            
        }

    } 
    
	private IEnumerator foco(float t){

		yield return new WaitForSeconds(t);
		animator.Play("foco");
	}

	public void retaurar(){
		lightbot.GetComponent<Transform>().localPosition = new Vector3(X, Y, Z);
		lightbot.GetComponent<Transform>().localRotation = new Quaternion(0, 0, 0, 0);
		timer_accion = new List<float>();
        n = 0;
        total_movimientos = 0;
		start = true;
	}

}

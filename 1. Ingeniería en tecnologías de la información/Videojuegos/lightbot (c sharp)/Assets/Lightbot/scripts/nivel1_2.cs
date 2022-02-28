using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class nivel1_2 : MonoBehaviour
{

    List<Estructura> acciones_main;
    GameObject lightbot;
    //posiciones iniciales Lightbot
    static float X = 0, Y = 1.5f, Z = 12;

    Animator animator;
    float posX, posY, posZ;
    float nuevoX, nuevoY, nuevoZ;
    int rotacion;
    int total_movimientos = 0;

    List<float> timer_accion;
	List<bool> contadores;

    float time = 0.0f;
    float time2 = 0.0f;
    float tiempo = 0;

    bool obtener_posicion = false;
    bool start = false;

    int n = 0;


    // Use this for initialization
    void Start()
    {
        lightbot = GameObject.Find("lightbot");
        animator = lightbot.GetComponent<Animator>();

		posX = lightbot.GetComponent<Transform>().localPosition.x;
        posY = lightbot.GetComponent<Transform>().localPosition.y;
        posZ = lightbot.GetComponent<Transform>().localPosition.z;
        rotacion = Mathf.FloorToInt(lightbot.GetComponent<Transform>().localRotation.y);


    }

    public void setDatos(List<Estructura> datos)
    {

        acciones_main = datos;

        timer_accion = new List<float>();
		contadores = new List<bool>();
        n = 0;
        total_movimientos = 0;

        for (int i = 0; i < acciones_main.Count; i++)
        {
            Debug.Log(acciones_main[i].getNombre());
            total_movimientos += acciones_main[i].getRepeticiones();
            for (int j = 0; j < acciones_main[i].getRepeticiones(); j++)
            {
                timer_accion.Add(0);
				contadores.Add(true);
				n++;
            }
        }
        //Debug.Log("total:" + total_movimientos);

        start = true;


        //string nombre_animacion = "";

        /*if (getNombre().Equals("f_caminar"))
        {
            nombre_animacion = "camina2";
        }

        float posX = lightbot.GetComponent<Transform>().localPosition.x;
        float posY = lightbot.GetComponent<Transform>().localPosition.y;
        float posZ = lightbot.GetComponent<Transform>().localPosition.z - 0.2f;

        if (obten_posicion == false)
        {
            posicion_actualZ = lightbot.GetComponent<Transform>().localPosition.z - 3;
            obten_posicion = true;
        }
        //animacion.Play(nombre_animacion);
        //Debug.Log("nombre: " + getNombre());
        if (timer < 1.0f)
        {
            animacion.Play(nombre_animacion);
            lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ);
            timer += (Time.deltaTime);
        }
        else
        {
            lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posicion_actualZ);
            movimiento = false;
            timer = 0.0f;
        }
        timer += (Time.deltaTime);*/
    }

    bool activo = true;

	float limite = 1.3f;
	int cont = 0;

    // Update is called once per frame
    void Update()
    { 

		if(start){

			for (int i = 0; i < acciones_main.Count; i++)
			{
				/*if (acciones_main[i].getNombre().Contains("f_caminar"))
				{
					animator.speed = 1;
					caminar(acciones_main[i].getRepeticiones(), i);
				}*/
				for (int j = 0; j < acciones_main[i].getRepeticiones(); j++)
				{
					//Debug.Log(cont + ", " +timer_accion[cont]);
					if (timer_accion[cont] <= 1.4f && contadores[cont] == true)
					{
						animator.speed = 1;
						//Debug.Log("aqui");
						if (acciones_main[i].getNombre().Contains("f_caminar"))
						    caminar(cont);

						timer_accion[cont] = time;
					}
					else
					{
						animator.speed = 0;
						lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ - 3);
						//timer_accion[cont] = 10.0f;
						contadores[cont] = false;
						cont++;
						time = 0.0f;

					}


				}
				Debug.Log(cont + ", " +timer_accion[cont]);
				if (cont >= acciones_main.Count){
					start = false;
					break;
				}

                
                //float t = Time.deltaTime;


                
            }         
			//Debug.Log(Time.deltaTime);
			//if (time >= 2)
                //time = 0;
			tiempo = Mathf.Round(time);

            time += Time.deltaTime;
		}


        //time2 += Time.deltaTime;
        
    }
    private void caminar(int c)
	{

		/*if (time > (1.3f * rep) && c == cont)
			animator.Play("camina");
		else{
			animator.speed = 0;
			time = 0.0f;
			cont++;
		}*/

		if (timer_accion[c] < 1.4f)
		{
			Debug.Log("camina");
			animator.Play("camina");
		}

			
		/*if (time > limite)
		{
			animator.speed = 0;
			time = 0.0f;
		}*/
		//Debug.Log(posZ);
	}

    private void foco()
    {

        //yield return new WaitForSeconds(t);
        animator.Play("foco");
    }

    public void retaurar()
    {
        lightbot.GetComponent<Transform>().localPosition = new Vector3(X, Y, Z);
        lightbot.GetComponent<Transform>().localRotation = new Quaternion(0, 0, 0, 0);
        timer_accion = new List<float>();
        n = 0;
        total_movimientos = 0;
        start = true;
    }
}

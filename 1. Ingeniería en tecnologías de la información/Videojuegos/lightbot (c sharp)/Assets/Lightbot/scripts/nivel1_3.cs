using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class nivel1_3 : MonoBehaviour
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

    public void setDatos(List<Estructura> datos)
    {

        acciones_main = datos;

        timer_accion = new List<float>();
        n = 0;
        total_movimientos = 0;

        for (int i = 0; i < acciones_main.Count; i++)
        {
            Debug.Log(acciones_main[i].getNombre());
            total_movimientos += acciones_main[i].getRepeticiones();
            for (int j = 0; j < acciones_main[i].getRepeticiones(); j++)
            {
                timer_accion.Add(0);
            }

        }
        //Debug.Log("total:" + total_movimientos);

        start = true;

        Ejecutar();



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


    void Update()
    {
        if (start)
        {
            //n = 0;

            //Debug.Log(tiempo);

            if (time >= total_movimientos)
            {
                start = false;
                time = 0;
            }
            else
                time += (Time.deltaTime);

            tiempo = Mathf.RoundToInt(time);

        }
    }

    // Update is called once per frame
    /*void Update()
    { 
        if(start){
            
            for (int i = 0; i < acciones_main.Count; i++){
                for (int j = 0; j < acciones_main[i].getRepeticiones(); j++)
                {

                    if (timer_accion[n] <= 1)
                    {
                        if (acciones_main[i].getNombre().Contains("f_caminar"))
                            caminar(acciones_main[i].getRepeticiones());

                        else if (acciones_main[i].getNombre().Contains("f_iluminar"))
                            foco();
                        
                        Debug.Log("timer_accion[" + n + "]: " + timer_accion[n]);
                        timer_accion[n] = (time);
                    }
                    else
                    {

                        obtener_posicion = false;
                        //Debug.Log("obtener posicion: " + obtener_posicion);
                        time = 0;
                        n++;
                    }
                    if (n >= total_movimientos)
                    {
                        start = false;
                        n = 0;
                        break;
                    }
                    //float t = Time.deltaTime;


                }
            }

            time += Time.deltaTime;
            time2 += Time.deltaTime;
        }

    }*/

    private void Ejecutar()
    {
        for (int i = 0; i < acciones_main.Count; i++)
        {
            for (int j = 0; j < acciones_main[i].getRepeticiones(); j++)
            {

                if (acciones_main[i].getNombre().Contains("f_caminar"))
                {

                    StartCoroutine(caminar(n + 1));
                }
                else if (acciones_main[i].getNombre().Contains("f_iluminar"))
                {
                    StartCoroutine(foco(n + 1));
                }

                n++;
            }
        }
    }

    private IEnumerator caminar(int t)
    {

        yield return new WaitForSeconds(t);

        posX = lightbot.GetComponent<Transform>().localPosition.x;
        posY = lightbot.GetComponent<Transform>().localPosition.y;
        posZ = lightbot.GetComponent<Transform>().localPosition.z;

        rotacion = Mathf.FloorToInt(lightbot.GetComponent<Transform>().localRotation.y);

        Debug.Log("rotacion: " + rotacion);
        if (rotacion >= -1 && rotacion <= 1)
        {

            /*if (obtener_posicion == false){
                //Debug.Log("Z: " + lightbot.GetComponent<Transform>().localPosition.z);
                nuevoZ = lightbot.GetComponent<Transform>().localPosition.z - (3);
                //activo = true;
                obtener_posicion = true;
            }
            nuevoX = posX;
            nuevoY = posY;
            Debug.Log("Z: " + posZ);
            //posZ -= 0.2f;*/
            //if(tiempo == t)
            //Debug.Log("posZ: " + posZ);
            //Debug.Log("entra caminar");
            lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ - 3);


        }
        /*if (time > 0.5f)
        {
            lightbot.GetComponent<Transform>().localPosition = new Vector3(nuevoX, nuevoY, nuevoZ);
            obtener_posicion = false;
        }*/
        /*if(time < 0.5f){
            
            //animator.Play("camina2");
            lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ);
        }
        else{
            
            lightbot.GetComponent<Transform>().localPosition = new Vector3(nuevoX, nuevoY, nuevoZ);
            //time = 0;
            //obtener_posicion = false;
            activo = false;
        }*/


    }

    private IEnumerator foco(int t)
    {

        yield return new WaitForSeconds(t);
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

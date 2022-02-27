using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
//#if UNITY_ANDROID
//using UnityEditor.Events;

//using UnityEditor.Build;
//#endif
//using UnityEditor.Events;

//XXXXXXXXXXXXXXXXXXXXXXXXXXX


public class canvas : MonoBehaviour
{

    public int nivel;
    //---------propiedades del objeto cliqueado----------
    GameObject objeto_click;
    RectTransform propiedades;

    int numBoton;
    int num_repetir = 0, num_fin = 0;
    //---------variables accion--------
    GameObject accion,
               suma,
               resta,
               texto,
               objeto_accion,
               objeto_suma,
               objeto_resta,
               objeto_texto;

    Text texto_accion;
    Image imagen_accion,
          imagen_suma,
          imagen_resta;
    Sprite sprite_accion,
           sprite_suma,
           sprite_resta;

    Button boton_accion, boton_suma, boton_resta;

    RectTransform propiedades_accion,
                  propiedades_suma,
                  propiedades_resta, propiedades_texto;


    string nombre_accion;

    bool movimiento = false;

    //----------variables panel main------------
    GameObject panel, panel_main;
    ScrollRect scrollRect;
    RectTransform rectTransform;



    //----------posicion inicial panel main----------
    static int posicion_inicialX = -65;
    static int posicion_inicialY = 730;

    //----------posiciones variables-----------
    int posicionX = posicion_inicialX,
        posicionY = posicion_inicialY;

    int[] clicks = new int[7] { 0, 0, 0, 0, 0, 0, 0 };
       
    //----------lista de funciones en el panel main--------
    List<string> nombre_acciones = new List<string>();
 
    List<Estructura> acciones_main = new List<Estructura>();


    int total_acciones = 0;

    GameObject lightbot;
    
	//posiciones iniciales Lightbot
    public float X, Y, Z;
    
    float timer = 0.0f;
    
	string getNombre()
    {
        return nombre_accion;
    }

    bool obten_posicion = false;


    //----------funcion que se activa con el click a un bloque de scratch---------
    public void button_click(string nombre)
    {
		//obtiene el nombre de la accion cleckeada
        objeto_click = GameObject.Find(nombre);

        propiedades = objeto_click.GetComponent<RectTransform>();


        nombre_accion = nombre;

        if (nombre.Equals("f_repetir")) { numBoton = 0; num_repetir++; }
        if (nombre.Equals("f_fin")) { numBoton = 1; }
        if (nombre.Equals("f_caminar")) { numBoton = 2; movimiento = true; }
        if (nombre.Equals("f_gira_izq")) numBoton = 3;
        if (nombre.Equals("f_gira_der")) numBoton = 4;
        if (nombre.Equals("f_saltar")) numBoton = 5;
        if (nombre.Equals("f_iluminar")) numBoton = 6;

        

        //se obtiene el objeto por su nombre
        panel = GameObject.Find("panel");
        panel_main = GameObject.Find("panel_main");
        scrollRect = panel.GetComponent<ScrollRect>();

        obten_posicion = false;

        if (!nombre.Equals("f_fin") || (nombre.Equals("f_fin") && num_repetir > num_fin))
        {
            //--------creacion de un nuevo objeto para colocar en el panel main--------
            accion = new GameObject();
            accion.transform.parent = panel_main.transform;
            accion.name = nombre + clicks[numBoton];
            //nombre_accion = accion.name;

            //componente RectTransform
            accion.AddComponent<RectTransform>();
            propiedades_accion = accion.GetComponent<RectTransform>();
            propiedades_accion.sizeDelta = propiedades.sizeDelta;
            if (nombre.Equals("f_fin")) { posicionX -= 18; posicionY += 5; num_fin++; }
            propiedades_accion.localPosition = new Vector2(posicionX, posicionY);
            propiedades_accion.localScale = new Vector3(1, 1, 1);

            //componente de Image
            accion.AddComponent<Image>();
            objeto_accion = GameObject.Find("sp_" + nombre);
            sprite_accion = objeto_accion.GetComponent<SpriteRenderer>().sprite;
            imagen_accion = accion.GetComponent<Image>();
            imagen_accion.type = Image.Type.Simple;
            imagen_accion.sprite = sprite_accion;

            //componente Button
            accion.AddComponent<Button>();
            boton_accion = accion.GetComponent<Button>();
            boton_accion.transition = Selectable.Transition.ColorTint;

            //se almacenan los datos de la nueva accion añadida en el main
            acciones_main.Add(new Estructura(1, accion.name));

            string ultima_accion = acciones_main[total_acciones].getNombre();

            //Estructura rep, cam;
            GameObject elemento = GameObject.Find(ultima_accion);

            /*se añade la funcion al evento Onclick del bloque y se le pasa como 
              parametro el nombre del bloque dinamico*/
            
			elemento.GetComponent<Button>().onClick.AddListener(() => remover_funcion(elemento.name));


            if (nombre.Equals("f_repetir")) { posicionX += 18; posicionY -= 40; }
            else if (nombre.Equals("f_fin")) posicionY -= 47;
            else { posicionY -= 44; }

            //---------------botones para funcion Repetir y Caminar-------------

            if (nombre.Equals("f_repetir") || nombre.Equals("f_caminar"))
            {
                //---------BOTON SUMA---------
                suma = new GameObject();
                suma.transform.parent = accion.transform;
                suma.name = "suma_" + accion.name;
                //componente RectTransform
                suma.AddComponent<RectTransform>();
                propiedades_suma = suma.GetComponent<RectTransform>();
                propiedades_suma.sizeDelta = new Vector2(30, 30);
                propiedades_suma.localPosition = new Vector2(145, 5);
                propiedades_suma.localScale = new Vector3(1, 1, 1);
                //componente Image
                suma.AddComponent<Image>();
                objeto_suma = GameObject.Find("sp_btn_suma");
                sprite_suma = objeto_suma.GetComponent<SpriteRenderer>().sprite;
                imagen_suma = suma.GetComponent<Image>();
                imagen_suma.type = Image.Type.Simple;
                imagen_suma.sprite = sprite_suma;
                //componente Button
                suma.AddComponent<Button>();
                boton_suma = suma.GetComponent<Button>();
                boton_suma.transition = Selectable.Transition.ColorTint;
                GameObject elemento_suma = GameObject.Find("suma_" + ultima_accion);
                elemento_suma.GetComponent<Button>().onClick.AddListener(() => repeticiones(ultima_accion, "suma"));


                //---------BOTON RESTA---------
                resta = new GameObject();
                resta.transform.parent = accion.transform;
                resta.name = "resta_" + accion.name;
                //componente RectTransform
                resta.AddComponent<RectTransform>();
                propiedades_resta = resta.GetComponent<RectTransform>();
                propiedades_resta.sizeDelta = new Vector2(30, 30);
                propiedades_resta.localPosition = new Vector2(105, 5);
                propiedades_resta.localScale = new Vector3(1, 1, 1);
                //componente Image
                resta.AddComponent<Image>();
                objeto_resta = GameObject.Find("sp_btn_resta");
                sprite_resta = objeto_resta.GetComponent<SpriteRenderer>().sprite;
                imagen_resta = resta.GetComponent<Image>();
                imagen_resta.type = Image.Type.Simple;
                imagen_resta.sprite = sprite_resta;
                //imagen_resta.raycastTarget = false;
                //componente Button
                resta.AddComponent<Button>();
                boton_resta = resta.GetComponent<Button>();
                boton_resta.transition = Selectable.Transition.ColorTint;
                GameObject elemento_resta = GameObject.Find("resta_" + ultima_accion);
                elemento_resta.GetComponent<Button>().onClick.AddListener(() => repeticiones(ultima_accion, "resta"));


                //---------TEXTO NUMERO---------
                texto = new GameObject();
                texto.transform.parent = accion.transform;
                texto.name = "num_" + accion.name;
                //componente RectTransform
                texto.AddComponent<RectTransform>();
                propiedades_texto = texto.GetComponent<RectTransform>();
                propiedades_texto.sizeDelta = new Vector2(30, 30);
                propiedades_texto.localPosition = new Vector2(60, 5);
                propiedades_texto.localScale = new Vector3(1, 1, 1);
                //componente Text
                texto.AddComponent<Text>();
                texto_accion = texto.GetComponent<Text>();
                texto_accion.text = "1";
                texto_accion.fontStyle = FontStyle.Normal;
                texto_accion.font = Font.CreateDynamicFontFromOSFont("Arial", 40);
                texto_accion.fontSize = 20;
                texto_accion.color = Color.black;
            }

            scrollRect.content = panel_main.GetComponent<RectTransform>();

            total_acciones++;

            clicks[numBoton]++;
        }

    }
    /*funcion que borra el bloque seleccionado del panel Main obteniendo
     el nombre como referencia*/
    private void remover_funcion(string nombre)
    {
        
        /*se obtiene el objeto tomando la busqueda por el nombre
        del bloque seleccionado*/
		GameObject accion_remover = GameObject.Find(nombre);
        


		RectTransform posicion = accion_remover.GetComponent<RectTransform>();

        int index = 0;
        for (int i = 0; i < acciones_main.Count; i++)
        {
            if (nombre.Equals(acciones_main[i].getNombre()))
            {
                index = i; //obtiene el indice del arreglo en donde contenga el nombre actual
                break;
            }
        }

        int size = acciones_main.Count;
        //Debug.Log(string.Format("index: {0}      nombre: {1}     num_acciones: {2}   caminar: {3}",index,nombre,size-1, caminar.Count));

        Vector2[] posiciones = new Vector2[size];

        for (int i = 0; i < size; i++)
            posiciones[i] = GameObject.Find(acciones_main[i].getNombre()).GetComponent<RectTransform>().localPosition;

        if (nombre.Contains("f_fin")) { posiciones[index].x += 18; posiciones[index].y -= 5; }

        if (size > 0 || index < size - 1)
        {
            for (int i = index + 1; i < size; i++)
            {
                if (nombre.Contains("f_repetir")) posiciones[i].x -= 18;
                RectTransform accion_mover = GameObject.Find(acciones_main[i].getNombre()).GetComponent<RectTransform>();
                accion_mover.localPosition = posiciones[i - 1];
            }
        }

        for (int i = 0; i < acciones_main.Count; i++)
        {
            if (nombre.Equals(acciones_main[i].getNombre()))
            {
                acciones_main.RemoveAt(i);
                break;
            }
        }

        total_acciones--;

        Destroy(accion_remover);
        posicionY += 44;

        if (nombre.Contains("f_repetir")) { num_repetir--; posicionX -= 18; posicionY -= 4; }
        if (nombre.Contains("f_fin")) { num_fin--; posicionX += 18; }

    }

    private void repeticiones(string nombre_funcion, string operacion)
    {
        for (int i = 0; i < acciones_main.Count; i++)
        {
            if (nombre_funcion.Equals(acciones_main[i].getNombre()))
            {
                //caso de suma
                if (operacion.Equals("suma"))
                {
                    //se incrementa el numero de repeticiones para esa accion
                    acciones_main[i].setRepeticiones(acciones_main[i].getRepeticiones() + 1);
                }
                //caso de resta
                else
                {
                    //se decrementa el numero de repeticiones para esa accion
                    if (acciones_main[i].getRepeticiones() > 1)
                        acciones_main[i].setRepeticiones(acciones_main[i].getRepeticiones() - 1);
                }
                Debug.Log("botones: " + nombre_funcion + "repeticiones: " + acciones_main[i].getRepeticiones());
                GameObject btn_suma = GameObject.Find("num_" + nombre_funcion);
                btn_suma.GetComponent<Text>().text = "" + acciones_main[i].getRepeticiones();
                break;
            }
        }
    }

	   
	int n = 0;
	Animator animator;

    float posX, posY, posZ;

	string nombre_bloque;
	GameObject bloque_colision;

	public int numero_focos;
	public int numero_bloques;

	int focos;
	int rotacion = 0;
	public int angulo;
	   
	void Start(){

        //se busca al objeto por el nombre para obtener los componentes del Lightbot
		lightbot = GameObject.Find("lightbot");
        //se obtiene el componente Animator del personaje
        animator = lightbot.GetComponent<Animator>();

		lightbot.GetComponent<Transform>().Rotate(0, angulo, 0);

		GameObject level = GameObject.Find("nivel");
		level.GetComponent<Text>().text = "NIVEL " + nivel + "";

		focos = numero_focos;
	}
    
	public void Play()
    {
		
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
				else if (acciones_main[i].getNombre().Contains("f_gira_izq"))
                {
                    StartCoroutine(gira(n + 1.5f, "izquierda"));
                }
				else if (acciones_main[i].getNombre().Contains("f_gira_der"))
                {
                    StartCoroutine(gira(n + 1.5f, "derecha"));
                }
                n++;
            }
        }
    }




    private IEnumerator caminar(float t)
    {
		//esta funcion sera ejecutada en t segundos
        yield return new WaitForSeconds(t);

        posX = lightbot.GetComponent<Transform>().localPosition.x;
        posY = lightbot.GetComponent<Transform>().localPosition.y;
        posZ = lightbot.GetComponent<Transform>().localPosition.z;
        
		lightbot = GameObject.Find("lightbot");

		if (rotacion == 720 || rotacion == 360 || rotacion == 0 || rotacion == -360 || rotacion == -720)
        {
            animator.Play("camina2");

            //se obtiene el nombre del bloque que pisa el lightbot
			nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            //se obtiene el objeto bloque
            bloque_colision = GameObject.Find(nombre_bloque);


			bool camina_sur = bloque_colision.GetComponent<bloque>().camina_sur;
            
			if(camina_sur)
				lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ - 3);          
        }
		else if (rotacion == 450 || rotacion == 90 || rotacion == -270 || rotacion == -630)
        {
            animator.Play("camina2");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool camina_oeste = bloque_colision.GetComponent<bloque>().camina_oeste;

			if (camina_oeste)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX - 3, posY, posZ);
        }
		else if (rotacion == 540 || rotacion == 180 || rotacion == -180 || rotacion == -540)
        {
            animator.Play("camina2");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool camina_norte = bloque_colision.GetComponent<bloque>().camina_norte;

			if (camina_norte)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY, posZ + 3);
        }
		else if (rotacion == -450 || rotacion == -90 || rotacion == 270 || rotacion == 630)
        {
            animator.Play("camina2");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool camina_este = bloque_colision.GetComponent<bloque>().camina_este;

			if (camina_este)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX + 3, posY, posZ);
        }

    }
    private IEnumerator saltar(float t)
    {
        yield return new WaitForSeconds(t);

        posX = lightbot.GetComponent<Transform>().localPosition.x;
        posY = lightbot.GetComponent<Transform>().localPosition.y;
        posZ = lightbot.GetComponent<Transform>().localPosition.z;


   

		nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
        bloque_colision = GameObject.Find(nombre_bloque);
		//bool salta = bloque_colision.GetComponent<bloque>().saltar;

		if (rotacion == 720 || rotacion == 360 || rotacion == 0 || rotacion == -360 || rotacion == -720)
        {
            animator.Play("foco");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool salta_sur = bloque_colision.GetComponent<bloque>().salta_sur;

			if (salta_sur)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ - 3);
			else
				lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ);
        }
        else if (rotacion == 450 || rotacion == 90 || rotacion == -270 || rotacion == -630)
        {
            animator.Play("foco");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool salta_oeste = bloque_colision.GetComponent<bloque>().salta_oeste;

			if (salta_oeste)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX - 3, posY + 2, posZ);
			else
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ);
        }
        else if (rotacion == 540 || rotacion == 180 || rotacion == -180 || rotacion == -540)
        {
            animator.Play("foco");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool salta_norte = bloque_colision.GetComponent<bloque>().salta_norte;

			if (salta_norte)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ + 3);
			else
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ);
        }
        else if (rotacion == -450 || rotacion == -90 || rotacion == 270 || rotacion == 630)
        {
            animator.Play("foco");

            nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
            bloque_colision = GameObject.Find(nombre_bloque);
			bool salta_este = bloque_colision.GetComponent<bloque>().salta_este;

			if (salta_este)
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX + 3, posY + 2, posZ);
			else
                lightbot.GetComponent<Transform>().localPosition = new Vector3(posX, posY + 2, posZ);
        }

    }

    private IEnumerator foco(float t)
    {

        yield return new WaitForSeconds(t);
        animator.Play("foco");

		nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
        bloque_colision = GameObject.Find(nombre_bloque);
		bool ilumina = bloque_colision.GetComponent<bloque>().foco;


		if (ilumina) {
			bloque_colision.GetComponent<Renderer> ().material.color = Color.yellow;
			//bloque_colision.GetComponent<bloque>().foco = false;
			focos--;
			if (focos == 0)
				StartCoroutine (final ());
		}
    }

	private IEnumerator gira(float t, string lado)
	{      
		yield return new WaitForSeconds(t);
		   
		nombre_bloque = lightbot.GetComponent<lightbot_colision>().getColision();
        bloque_colision = GameObject.Find(nombre_bloque);

        //se activa la animacion de giro
		animator.Play("gira");   

		if (lado.Equals("izquierda"))
		    angulo = -90;      
		else
			angulo = 90;

        //se hace rotacion del lightbot
		lightbot.GetComponent<Transform>().Rotate(0, angulo, 0);

		rotacion += angulo;
		Debug.Log("rotacion: " + rotacion);
    }

	private IEnumerator final(){
		yield return new WaitForSeconds (1);

		if(nivel < 2)
			SceneManager.LoadScene ("nivel" + (nivel + 1));
	}

    public void retaurar()
    {
        lightbot.GetComponent<Transform>().localPosition = new Vector3(X, Y, Z);
		lightbot.GetComponent<Transform>().localRotation = new Quaternion(0, 0, 0, 0);

		for (int i = 1; i <= numero_bloques; i++){
			bloque_colision = GameObject.Find("bloque" + i);
			if (bloque_colision.GetComponent<bloque>().foco)
			{
				bloque_colision.GetComponent<Renderer>().material.color = Color.blue;
				focos = numero_focos;
			}
		}
		rotacion = 0;
        n = 0;
        
    }
}
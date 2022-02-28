using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
//#if UNITY_ANDROID
//using UnityEditor.Events;

//using UnityEditor.Build;
//#endif
//using UnityEditor.Events;

//XXXXXXXXXXXXXXXXXXXXXXXXXXX


public class funciones_canvas : MonoBehaviour
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

    //----------Lista de contadores para las funciones de caminar y repetir-------------
    /*List<int> caminar = new List<int>();
	List<int> index_caminar = new List<int>();
    List<string> nombre_caminar = new List<string>();

    List<int> repetir = new List<int>();
	List<int> index_repetir = new List<int>();
    List<string> nombre_repetir = new List<string>();*/

	//----------lista de funciones en el panel main--------
    List<string> nombre_acciones = new List<string>();

	/*struct Estructura{
		public int repeticiones;
        public string nombre;
		public Estructura(int r, string n){
			repeticiones = r;
			nombre = n;
		}
	}*/

	List<Estructura> acciones_main = new List<Estructura>();
 

	int total_acciones = 0;

    GameObject lightbot;

    float posicion_actualX, posicion_actualY, posicion_actualZ;


    float timer = 0.0f;
    void Start() {


	}   
    string getNombre()
    {
        return nombre_accion;
    }

    bool obten_posicion = false;

       
    //----------funcion que se activa con el click---------
    public void button_click(string nombre)
    {
        
		nombre_accion = nombre;

        if (nombre.Equals("f_repetir")) { numBoton = 0; num_repetir++; }
        if (nombre.Equals("f_fin")) { numBoton = 1; }
		if (nombre.Equals("f_caminar")) { numBoton = 2; movimiento = true;}
        if (nombre.Equals("f_gira_izq")) numBoton = 3;
        if (nombre.Equals("f_gira_der")) numBoton = 4;
        if (nombre.Equals("f_saltar")) numBoton = 5;
        if (nombre.Equals("f_iluminar")) numBoton = 6;

        //obtiene el nombre de la accion cleckeada
        objeto_click = GameObject.Find(nombre);

        propiedades = objeto_click.GetComponent<RectTransform>();

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
			GameObject elemento = GameObject.Find( ultima_accion );
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

    private void remover_funcion(string nombre)
    {
		GameObject accion_remover = GameObject.Find(nombre);
        RectTransform posicion = accion_remover.GetComponent<RectTransform>();

        int index = 0;
		for (int i = 0; i < acciones_main.Count; i++){
			if (nombre.Equals(acciones_main[i].getNombre())){
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

		if(size > 0 || index < size-1){
			for (int i = index + 1; i < size; i++){
                if (nombre.Contains("f_repetir")) posiciones[i].x -= 18;
				RectTransform accion_mover = GameObject.Find(acciones_main[i].getNombre()).GetComponent<RectTransform>();
                accion_mover.localPosition = posiciones[i - 1];
            }
		}        

        for (int i = 0; i < acciones_main.Count; i++){
			if(nombre.Equals(acciones_main[i].getNombre())){
				acciones_main.RemoveAt(i);
				break;
			}
		}
  
		total_acciones --;

        Destroy(accion_remover);
        posicionY += 44;
        
		if (nombre.Contains("f_repetir")){num_repetir--; posicionX -= 18; posicionY -= 4;}
        if (nombre.Contains("f_fin")) { num_fin--; posicionX += 18; }

    }

	private void repeticiones(string nombre_funcion, string operacion){
        for (int i = 0; i < acciones_main.Count; i++){
			if (nombre_funcion.Equals(acciones_main[i].getNombre())){
                //caso de suma
				if (operacion.Equals("suma")){
					//se incrementa el numero de repeticiones para esa accion
					acciones_main[i].setRepeticiones(acciones_main[i].getRepeticiones() + 1);               
				}
				//caso de resta
				else{
					//se decrementa el numero de repeticiones para esa accion
					if(acciones_main[i].getRepeticiones() > 1)
						acciones_main[i].setRepeticiones(acciones_main[i].getRepeticiones() - 1);
                }
				Debug.Log("botones: " + nombre_funcion + "repeticiones: " + acciones_main[i].getRepeticiones());
				GameObject btn_suma = GameObject.Find("num_" + nombre_funcion);
				btn_suma.GetComponent<Text>().text = "" + acciones_main[i].getRepeticiones();
                break;
            }
		}
	}

	public void button_play(){

		GameObject panel_controles = GameObject.Find("panel_controles");   

		if(total_acciones > 0){
			if (nivel == 1){
				Nivel1 nivel1 = panel_controles.GetComponent<Nivel1>();
                nivel1.setDatos(acciones_main);
            }
		}        
	}

	void Update()
    {      
        
    }  
}

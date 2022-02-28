using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace algebraLineal
{
    public partial class Operaciones1 : Form
    {
        int boton;
        public double[] numeradorA = new double[9];
        public double[] denominadorA = new double[9];
        public double[] numeradorB = new double[9];
        public double[] denominadorB = new double[9];
        public string[] matrizA = new string[9];
        public string[] matrizB = new string[9];

        List<Label> cajas = new List<Label>();
        string modo="fraccion";

        public Operaciones1(int numBoton)
        {
            InitializeComponent();
            this.boton = numBoton;
            //guardo los valores de la matriz A en un arreglo de cadenas
        }
        private void Operaciones1_Load(object sender, EventArgs e)
        {
             
            this.matrizA = new string[9];
            matrizA[0] = ma11.Text;
            this.matrizA[1] = ma12.Text;
            this.matrizA[2] = ma13.Text;
            this.matrizA[3] = ma21.Text;
            this.matrizA[4] = ma22.Text;
            this.matrizA[5] = ma23.Text;
            this.matrizA[6] = ma31.Text;
            this.matrizA[7] = ma32.Text;
            this.matrizA[8] = ma33.Text;
            //guardo los valores de la matriz B en un arreglo de cadenas
            this.matrizB[0] = mb11.Text;
            this.matrizB[1] = mb12.Text;
            this.matrizB[2] = mb13.Text;
            this.matrizB[3] = mb21.Text;
            this.matrizB[4] = mb22.Text;
            this.matrizB[5] = mb23.Text;
            this.matrizB[6] = mb31.Text;
            this.matrizB[7] = mb32.Text;
            this.matrizB[8] = mb33.Text;

            cajas.Add(r11);
            cajas.Add(r12);
            cajas.Add(r13);
            cajas.Add(r21);
            cajas.Add(r22);
            cajas.Add(r23);
            cajas.Add(r31);
            cajas.Add(r32);
            cajas.Add(r33);
            
            fraccion_btn.Enabled = false;

            for (int i = 0; i < 9; i++)
            {
                fraccionesA(i);
                fraccionesB(i);
            }
            if (boton == 1 || boton == 2 || boton == 3)
            {
                if (boton == 1) { text1.Text = "SUMA DE MATRICES";  text3.Text = "A + B = "; }
                if (boton == 2) { text1.Text = "RESTA DE MATRICES"; text3.Text = "A - B = "; }
                if (boton == 3) { text1.Text = "RESTA DE MATRICES"; text3.Text = "B - A = "; }
                suma_resta();
            }
            else if (boton == 4 || boton == 5)
            {
                if (boton == 4) { text1.Text = "MULTIPLICACION DE MATRICES"; text3.Text = "A x B = "; }
                if (boton == 5) { text1.Text = "MULTIPLICACION DE MATRICES"; text3.Text = "B x A = "; }
                multiplicacion(0, 0, 1, 3, 2, 6, 0);
                multiplicacion(0, 1, 1, 4, 2, 7, 1);
                multiplicacion(0, 2, 1, 5, 2, 8, 2);
                multiplicacion(3, 0, 4, 3, 5, 6, 3);
                multiplicacion(3, 1, 4, 4, 5, 7, 4);
                multiplicacion(3, 2, 4, 5, 5, 8, 5);
                multiplicacion(6, 0, 7, 3, 8, 6, 6);
                multiplicacion(6, 1, 7, 4, 8, 7, 7);
                multiplicacion(6, 2, 7, 5, 8, 8, 8);
            }
            ModoSuma();            
        }
        private void fraccionesA(int a)
        {
            string string1="";
            string string2="";
            int i, aux=0;
            bool division = false;
            for (i = 0; i < matrizA[a].Length; i++)
            {
                if (matrizA[a].ElementAt(i) != '/')
                {
                    string1 = string1 + matrizA[a].ElementAt(i);
                }
                else
                {
                    aux = i + 1;
                    division = true;
                    break;
                }
            }
            if (division == true)
            {
                for (i = aux; i < matrizA[a].Length; i++)
                {
                    string2 = string2 + matrizA[a].ElementAt(i);
                }
            }
            else
            {
                string2 = "1";
            }
            //int.TryParse(stringA, out numeradorA[a]);           
            this.numeradorA[a] = double.Parse(string1);
            this.denominadorA[a] = double.Parse(string2);

            numeradorConPunto(numeradorA[a], denominadorA[a], a, 'A');
        }
        private void fraccionesB(int a)
        {
            string string1 = "";
            string string2 = "";
            int i, aux = 0;
            bool division = false;
            for (i = 0; i < matrizB[a].Length; i++)
            {
                if (matrizB[a].ElementAt(i) != '/')
                {
                    string1 = string1 + matrizB[a].ElementAt(i);
                }
                else
                {
                    aux = i + 1;
                    division = true;
                    break;
                }
            }

            if (division == true)
            {
                for (i = aux; i < matrizB[a].Length; i++)
                {
                    string2 = string2 + matrizB[a].ElementAt(i);
                }
            }
            else
            {
                string2 = "1";
            }
            //int.TryParse(stringA, out numeradorA[a]);             
            this.numeradorB[a] = double.Parse(string1);
            this.denominadorB[a] = double.Parse(string2);

            numeradorConPunto(numeradorB[a], denominadorB[a], a, 'B');
            //MessageBox.Show("" + numeradorA[a]);
        }

        private void numeradorConPunto(double numerador, double denominador, int indice, char AB)
        {
            //>>>>>>>>>>> Averigua si en el numerador se detecta un punto <<<<<<<<<<<<<<<<<<<<<<<<
            bool punto = false, n = false;
            string numB = numerador.ToString();
            double auxiliar = numerador;
            int j, x = 2;

            for (j = 0; j < numB.Length; j++)
            {
                if (numB.ElementAt(j) == '.')
                {
                    punto = true;
                }
            }
            if (punto == true)
            {
                do
                {
                    numerador = numerador * x;
                    numB = numerador.ToString();
                    //MessageBox.Show(numB);
                    for (j = 0; j < numB.Length; j++)
                    {
                        if (numB.ElementAt(j) == '.')
                        {
                            break;
                        }
                        else if (j == numB.Length - 1)
                        {
                            n = true;
                        }
                    }
                    numerador = auxiliar;
                    x++;

                }
                while (n == false);
                numerador = double.Parse(numB);
                denominador = x - 1;
                if (AB == 'A')
                {
                    this.numeradorA[indice] = numerador;
                    this.denominadorA[indice] = denominador;
                }
                else
                {
                    this.numeradorB[indice] = numerador;
                    this.denominadorB[indice] = denominador;
                }
            }            
        }




        double[] num = new double[9];
        double[] den = new double[9];
        double[] numero = new double[9];
        private void suma_resta()
        {            
            int i;
            for (i = 0; i < 9; i++)
            {
                if (boton == 1)
                {
                    num[i] = (this.numeradorA[i] * this.denominadorB[i]) + (this.numeradorB[i] * this.denominadorA[i]);
                }
                else if (boton == 2)
                {
                    num[i] = (this.numeradorA[i] * this.denominadorB[i]) - (this.numeradorB[i] * this.denominadorA[i]);
                }
                else if (boton == 3)
                {
                    num[i] = (this.numeradorB[i] * this.denominadorA[i]) - (this.numeradorA[i] * this.denominadorB[i]);
                }
                den[i] = this.denominadorA[i] * this.denominadorB[i];

                for (int j = 2; j < 10; j++)
                {
                    do
                    {
                        if (num[i] % j == 0 && den[i] % j == 0)
                        {
                            num[i] = num[i] / j;
                            den[i] = den[i] / j;
                        }
                        else
                        {
                            break;
                        }
                    } while (num[i] > 1 && den[i] > 1);
                }
                numero[i] = num[i] / den[i];
            }  
            
            //r11.Text = num[0].ToString() + "/" + den[0].ToString();
            
        }
        
        double numerador, denominador;

        public void multiFraccion(double num1, double den1, double num2, double den2)
        {            
            this.numerador = num1 * num2;
            this.denominador = den1 * den2;
            
        }
        //List<double> numeradores=new List<double>();
        //List<double> denominadores = new List<double>();
        //double[] numeradores = new double[9];
        //double[] denominadores = new double[9];
        public void multiplicacion(int num1, int num2, int num3, int num4, int num5, int num6, int n)
        {
            double []numeradores=new double[3];
            double []denominadores=new double[3];
            double numerador, denominador;

            if (boton == 4)
            {
                multiFraccion(numeradorA[num1], denominadorA[num1], numeradorB[num2], denominadorB[num2]);
                numeradores[0] = this.numerador;
                denominadores[0] = this.denominador;
                multiFraccion(numeradorA[num3], denominadorA[num3], numeradorB[num4], denominadorB[num4]);
                numeradores[1] = this.numerador;
                denominadores[1] = this.denominador;
                multiFraccion(numeradorA[num5], denominadorA[num5], numeradorB[num6], denominadorB[num6]);
                numeradores[2] = this.numerador;
                denominadores[2] = this.denominador;
            }
            else if (boton == 5)
            {
                multiFraccion(numeradorB[num1], denominadorB[num1], numeradorA[num2], denominadorA[num2]);
                numeradores[0] = this.numerador;
                denominadores[0] = this.denominador;
                multiFraccion(numeradorB[num3], denominadorB[num3], numeradorA[num4], denominadorA[num4]);
                numeradores[1] = this.numerador;
                denominadores[1] = this.denominador;
                multiFraccion(numeradorB[num5], denominadorB[num5], numeradorA[num6], denominadorA[num6]);
                numeradores[2] = this.numerador;
                denominadores[2] = this.denominador;
            }

            numerador = (numeradores[0] * denominadores[1])+(denominadores[0]*numeradores[1]);
            denominador = denominadores[0] * denominadores[1];


            numerador = (numerador * denominadores[2])+(denominador*numeradores[2]);
            denominador = denominador * denominadores[2];
            //MessageBox.Show("num:" + this.numerador + " den:" + this.denominador);
            for (int j = 2; j < 10; j++)
            {
                do
                {
                    if (numerador % j == 0 && denominador % j == 0)
                    {
                        numerador = numerador / j;
                        denominador = denominador / j;
                    }
                    else
                    {
                        break;
                    }
                } while (numerador > 1 && denominador > 1);
            }
            //cajas.ElementAt(n).Text = "" + numerador + "/" + denominador;
            numero[n] = numerador / denominador;
            this.num[n] = numerador;
            this.den[n] = denominador;
        }
        


        private void fraccion_btn_Click(object sender, EventArgs e)
        {
            modo = "fraccion";
            ModoSuma();
            fraccion_btn.Enabled = false;
            decimal_btn.Enabled = true;
        }

        private void decimal_btn_Click(object sender, EventArgs e)
        {
            modo = "decimal";
            ModoSuma();
            decimal_btn.Enabled = false;
            fraccion_btn.Enabled = true;
        }
        public void ModoSuma()
        {
            for (int i = 0; i < 9; i++)
            {
                if (modo == "fraccion")
                {
                    if (den[i] == 1)
                    {
                        cajas.ElementAt(i).Text = this.numero[i].ToString();
                    }
                    else
                    {
                        cajas.ElementAt(i).Text = this.num[i].ToString() + "/" + this.den[i].ToString();
                        /*if (boton == 1 || boton == 2 || boton == 3)
                        {
                            cajas.ElementAt(i).Text = this.num[i].ToString() + "/" + this.den[i].ToString();
                        }
                        else
                        {
                            cajas.ElementAt(i).Text = this.numeradores[i] + "/" + this.denominadores[i];
                        }*/
                        
                    }
                }
                else
                {
                    cajas.ElementAt(i).Text = this.numero[i].ToString();
                }
            }
        }

        private void ma11_Click(object sender, EventArgs e)
        {
            
        }       
    }
}
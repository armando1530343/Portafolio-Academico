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
    public partial class Operaciones2 : Form
    {
        int boton;
        public Operaciones2(int numBoton)
        {
            InitializeComponent();
            boton = numBoton;
            
        }

        public double[] numerador = new double[10];
        public double[] denominador = new double[10];
        public string[] matriz = new string[10];
        List<Label> cajas = new List<Label>();
        string modo = "fraccion";
        string tipo;

        private void Operaciones2_Load(object sender, EventArgs e)
        {
            matriz[0] = mat11.Text;
            matriz[1] = mat12.Text;
            matriz[2] = mat13.Text;
            matriz[3] = mat21.Text;
            matriz[4] = mat22.Text;
            matriz[5] = mat23.Text;
            matriz[6] = mat31.Text;
            matriz[7] = mat32.Text;
            matriz[8] = mat33.Text;

            cajas.Add(op11);
            cajas.Add(op12);
            cajas.Add(op13);
            cajas.Add(op21);
            cajas.Add(op22);
            cajas.Add(op23);
            cajas.Add(op31);
            cajas.Add(op32);
            cajas.Add(op33);

            for (int i = 0; i < 9; i++)
            {
                fracciones(i);
            }
            determinante();

           
            //MessageBox.Show("Determinante: " + numerador[9] + "/" + denominador[9]);

            adjunta(0, 4, 5, 7, 8);
            adjunta(1, 3, 5, 6, 8);
            adjunta(2, 3, 4, 6, 7);
            adjunta(3, 1, 2, 7, 8);
            adjunta(4, 0, 2, 6, 8);
            adjunta(5, 0, 1, 6, 7);
            adjunta(6, 1, 2, 4, 5);
            adjunta(7, 0, 2, 3, 5);
            adjunta(8, 0, 1, 3, 4);

            fraccion_btn.Enabled = false;
            switch (boton)
            {
                case 1:
                    tipo = "inversa";
                    inversa(); 
                    MostrarMatriz(tipo);break;
                case 2:
                    tipo = "inversa";
                    inversa(); 
                    MostrarMatriz(tipo);break;
                case 3:
                    text1.Text = "MATRIZ ADJUNTA"; text2.Text="A = "; text3.Text="Adj(A)";
                    tipo = "adjunta";
                    MostrarMatriz(tipo); break;
                case 4:
                    tipo = "adjunta";
                    text1.Text = "MATRIZ ADJUNTA"; text2.Text="B = "; text3.Text="Adj(B)";
                    MostrarMatriz(tipo); break;
                case 5:
                    text1.Text = "MATRIZ TRANSPUESTA"; text2.Text="A = "; text3.Text="A(t) = ";
                    decimal_btn.Enabled = false;
                    break;
                case 6:
                    text1.Text = "MATRIZ TRANSPUESTA"; text2.Text = "B = "; text3.Text = "B(t) = ";
                    decimal_btn.Enabled = false;
                    break;
            }

            
        }

        private void fracciones(int a)
        {
            string string1 = "";
            string string2 = "";
            int i, aux = 0;
            bool division = false;
            for (i = 0; i < matriz[a].Length; i++)
            {
                if (matriz[a].ElementAt(i) != '/')
                {
                    string1 = string1 + matriz[a].ElementAt(i);
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
                for (i = aux; i < matriz[a].Length; i++)
                {
                    string2 = string2 + matriz[a].ElementAt(i);
                }
            }
            else
            {
                string2 = "1";
            }
            //int.TryParse(stringA, out numeradorA[a]);           
            this.numerador[a] = double.Parse(string1);
            this.denominador[a] = double.Parse(string2);

            numeradorConPunto(numerador[a], denominador[a], a);
        }
        private void numeradorConPunto(double numerador, double denominador, int indice)
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
                this.numerador[indice] = numerador;
                this.denominador[indice] = denominador;
            }
        }
        double numDet, denDet;
        private double determinante()
        {
            double[] detNum = new double[3];
            double[] detDen = new double[3];
            //double numDet, denDet;
            double num1, num2, den1, den2, numerador, denominador;
            double numero;
            num1 = this.numerador[4] * this.numerador[8];
            den1 = this.denominador[4] * this.denominador[8];
            num2 = this.numerador[7] * this.numerador[5];
            den2 = this.denominador[7] * this.denominador[5];
            numerador = (num1 * den2) - (den1 * num2);
            denominador = den1 * den2;
            detNum[0] = this.numerador[0] * numerador;
            detDen[0] = this.denominador[0] * denominador;

            num1 = this.numerador[3] * this.numerador[8];
            den1 = this.denominador[3] * this.denominador[8];
            num2 = this.numerador[6] * this.numerador[5];
            den2 = this.denominador[6] * this.denominador[5];
            numerador = (num1 * den2) - (den1 * num2);
            denominador = den1 * den2;
            detNum[1] = (-1 * this.numerador[1]) * numerador;
            detDen[1] = this.denominador[1] * denominador;

            num1 = this.numerador[3] * this.numerador[7];
            den1 = this.denominador[3] * this.denominador[7];
            num2 = this.numerador[6] * this.numerador[4];
            den2 = this.denominador[6] * this.denominador[4];
            numerador = (num1 * den2) - (den1 * num2);
            denominador = den1 * den2;
            detNum[2] = this.numerador[2] * numerador;
            detDen[2] = this.denominador[2] * denominador;

            numDet = (detNum[0] * detDen[1]) + (detDen[0] * detNum[1]);
            denDet = detDen[0] * detDen[1];

            numDet = (numDet * detDen[2]) + (denDet * detNum[2]);
            denDet = denDet * detDen[2];


            for (int j = 2; j < 200; j++)
            {
                do
                {
                    if (numDet % j == 0 && denDet % j == 0)
                    {
                        numDet = numDet / j;
                        denDet = denDet / j;
                    }
                    else
                    {
                        break;
                    }
                } while (numDet > 1 && denDet > 1);
            }
            numero = numDet / denDet;
            //MessageBox.Show("Determinante = " + numDet + "/" + denDet);

            
            return numero;
        }

        double[] num = new double[10];
        double[] den = new double[10];
        double[] numero = new double[10];
        double[] numInv = new double[10];
        double[] denInv = new double[10];
        double[] numeroInv = new double[10];
        private void simplificarAdjunta(int i)
        {
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
        private void simplificarInversa(int i)
        {
            for (int j = 2; j < 10; j++)
            {
                do
                {
                    if (numInv[i] % j == 0 && denInv[i] % j == 0)
                    {
                        numInv[i] = numInv[i] / j;
                        denInv[i] = denInv[i] / j;
                    }
                    else
                    {
                        break;
                    }
                } while (numInv[i] > 1 && denInv[i] > 1);
            }
            numeroInv[i] = numInv[i] / denInv[i];
        }

        private void adjunta(int i, int a, int b, int c, int d)
        {
            
            double n1, n2, d1, d2;
            n1 = numerador[a] * numerador[d];
            d1 = denominador[a] * denominador[d];

            n2 = numerador[c] * numerador[b];
            d2 = denominador[c] * denominador[b];

            //MessageBox.Show("(" + n1 + "/" + d1 + ")(" + n2 + "/" + d2 + ")");

            num[i] = (n1 * d2) - (d1 * n2);
            den[i] = d1 * d2;

            if (i == 1 || i == 3 || i == 5 || i == 7)
            {
                num[i] = -num[i];
            }

            simplificarAdjunta(i);
            numero[i] = num[i] / den[i];
            
        }

        private void inversa()
        {
            int i;
            double[] cont = new double[9];
            double[] cont2 = new double[9];
            int j=0;
            for (i = 0; i < 9; i++)
            {
                numInv[i] = denDet * num[i];
                denInv[i] = numDet * den[i];
                simplificarInversa(i);
                if (i != 0 && i != 4 && i != 8)
                {
                    cont[i] = numInv[i];
                    cont2[i] = denInv[i];
                    //j++;
                }
                //cajas.ElementAt(i).Text = "" + numInv[i] + "/" + denInv[i];
            }
            numInv[1] = cont[3]; denInv[1] = cont2[3];
            numInv[2] = cont[6]; denInv[2] = cont2[6];
            numInv[3] = cont[1]; denInv[3] = cont2[1];
            numInv[5] = cont[7]; denInv[5] = cont2[7];
            numInv[6] = cont[2]; denInv[6] = cont2[2];
            numInv[7] = cont[5]; denInv[7] = cont2[5];
            
        }
        private void MostrarMatriz(string tipo)
        {
            int i;            
            for (i = 0; i < 9; i++)
            {
                if (tipo == "adjunta")
                {
                    if (modo == "fraccion")
                    {
                        if (den[i] == 1 || num[i] == 0 || num == den)
                        {
                            cajas.ElementAt(i).Text = "" + numero[i];
                        }
                        else
                        {
                            cajas.ElementAt(i).Text = "" + num[i] + "/" + den[i];
                        }
                    }
                    else
                    {
                        cajas.ElementAt(i).Text = "" + numero[i];
                    } 
                }
                else
                {
                    if (modo == "fraccion")
                    {
                        if (denInv[i] == 1 || numInv[i] == 0 || numInv == denInv)
                        {
                            cajas.ElementAt(i).Text = "" + numeroInv[i];
                        }
                        else
                        {
                            cajas.ElementAt(i).Text = "" + numInv[i] + "/" + denInv[i];
                        }
                    }
                    else
                    {
                        cajas.ElementAt(i).Text = "" + numeroInv[i];
                    } 
                }
                               
            }
        }

        private void fraccion_btn_Click(object sender, EventArgs e)
        {
            fraccion_btn.Enabled = false;
            decimal_btn.Enabled = true;
            modo = "fraccion";
            MostrarMatriz(tipo);
        }

        private void decimal_btn_Click(object sender, EventArgs e)
        {
            decimal_btn.Enabled = false;
            fraccion_btn.Enabled = true;            
            modo = "decimal";
            MostrarMatriz(tipo);
        }
    }
}

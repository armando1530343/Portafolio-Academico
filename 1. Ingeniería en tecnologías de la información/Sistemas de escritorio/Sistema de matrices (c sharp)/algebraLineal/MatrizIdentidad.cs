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
    public partial class MatrizIdentidad : Form
    {
        double[] numeradorA = new double[18];
        double[] denominadorA = new double[18];
        double[] inNumerador = new double[9];
        double[] inDenominador = new double[9];
        string[] number = new string[18];
        double[] numero = new double[18];
        string[] matrizA = new string[18];
        List<Label> cajas1 = new List<Label>();
        List<Label> cajas2 = new List<Label>();
        List<Label> cajas3 = new List<Label>();
        public MatrizIdentidad()
        {
            InitializeComponent();
        }

        private void MatrizIdentidad_Load(object sender, EventArgs e)
        {
            cajas1.Add(m11);
            cajas1.Add(m12);
            cajas1.Add(m13);
            cajas1.Add(m21);
            cajas1.Add(m22);
            cajas1.Add(m23);
            cajas1.Add(m31);
            cajas1.Add(m32);
            cajas1.Add(m33);

            cajas2.Add(mb11);
            cajas2.Add(mb12);
            cajas2.Add(mb13);
            cajas2.Add(mb21);
            cajas2.Add(mb22);
            cajas2.Add(mb23);
            cajas2.Add(mb31);
            cajas2.Add(mb32);
            cajas2.Add(mb33);

            /*for (int i = 0; i < 9; i++)
            {
                fraccionesA(i);
            }*/
        }
        private void fraccionesA(int a)
        {
            string string1 = "";
            string string2 = "";
            int i, aux = 0;
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
            this.numero[a] = this.numeradorA[a] / this.denominadorA[a];
            this.number[a] = "" + this.numeradorA[a] + "/" + this.denominadorA[a];

            numeradorConPunto(numeradorA[a], denominadorA[a], a);
        }
        private void simplificar(int i)
        {
            for (int j = 2; j < 10; j++)
            {
                do
                {
                    if (numeradorA[i] % j == 0 && denominadorA[i] % j == 0)
                    {
                        numeradorA[i] = numeradorA[i] / j;
                        denominadorA[i] = denominadorA[i] / j;
                    }
                    else
                    {
                        break;
                    }
                } while (numeradorA[i] > 1 && denominadorA[i] > 1);
            }
            numero[i] = numeradorA[i] / denominadorA[i];
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
                this.numeradorA[indice] = numerador;
                this.denominadorA[indice] = denominador;
                this.number[indice] = "" + numerador + "/" + denominador;                
            }
        }

        private void gaussJordan()
        {
            int i;
            //double auxNumerador, auxDenominador;
            bool cambio = false;

            in11.Text = "" + 1; in12.Text = "" + 0; in13.Text = "" + 0;
            in21.Text = "" + 0; in22.Text = "" + 1; in23.Text = "" + 0;
            in31.Text = "" + 0; in32.Text = "" + 0; in33.Text = "" + 1;

            cajas3.Add(in11);
            cajas3.Add(in12);
            cajas3.Add(in13);
            cajas3.Add(in21);
            cajas3.Add(in22);
            cajas3.Add(in23);
            cajas3.Add(in31);
            cajas3.Add(in32);
            cajas3.Add(in33);


            for (i = 0; i < 18; i++)
            {
                if (i < 9)
                {
                    matrizA[i] = cajas1.ElementAt(i).Text;
                    fraccionesA(i);
                    if (denominadorA[i] == 1 || numeradorA[i] == 0)
                    {
                        cajas2.ElementAt(i).Text = "" + numero[i];
                    }
                    else
                    {
                        cajas2.ElementAt(i).Text = "" + numeradorA[i] + "/" + denominadorA[i];
                    }
                }
                else
                {
                    matrizA[i] = cajas3.ElementAt(i-9).Text;
                    fraccionesA(i);
                    if (denominadorA[i] == 1 || numeradorA[i] == 0)
                    {
                        cajas3.ElementAt(i-9).Text = "" + numero[i];
                    }
                    else
                    {
                        cajas3.ElementAt(i-9).Text = "" + numeradorA[i] + "/" + denominadorA[i];
                    }
                }                             
            }

            if (numero[0] == 0 && numero[3] != 0 && cambio == false)
            {
                if (denominadorA[3] == 1 || numeradorA[3] == 0) { mb11.Text = "" + numero[3]; } else { mb11.Text = "" + numeradorA[3] + "/" + denominadorA[3]; }
                if (denominadorA[4] == 1 || numeradorA[4] == 0) { mb12.Text = "" + numero[4]; } else { mb12.Text = "" + numeradorA[4] + "/" + denominadorA[4]; }
                if (denominadorA[5] == 1 || numeradorA[5] == 0) { mb13.Text = "" + numero[5]; } else { mb13.Text = "" + numeradorA[5] + "/" + denominadorA[5]; }
                if (denominadorA[0] == 1 || numeradorA[0] == 0) { mb21.Text = "" + numero[0]; } else { mb21.Text = "" + numeradorA[0] + "/" + denominadorA[0]; }
                if (denominadorA[1] == 1 || numeradorA[1] == 0) { mb22.Text = "" + numero[1]; } else { mb22.Text = "" + numeradorA[1] + "/" + denominadorA[1]; }
                if (denominadorA[2] == 1 || numeradorA[2] == 0) { mb23.Text = "" + numero[2]; } else { mb23.Text = "" + numeradorA[2] + "/" + denominadorA[2]; }
                in11.Text = "" + 0; in12.Text = "" + 1; in13.Text = "" + 0;
                in21.Text = "" + 1; in22.Text = "" + 0; in23.Text = "" + 0;
                cambio = true;
            }
            if (numero[0] == 0 && numero[6] != 0 && cambio == false)
            {
                if (denominadorA[6] == 1 || numeradorA[6] == 0) { mb11.Text = "" + numero[6]; } else { mb11.Text = "" + numeradorA[6] + "/" + denominadorA[6]; }
                if (denominadorA[7] == 1 || numeradorA[7] == 0) { mb12.Text = "" + numero[7]; } else { mb12.Text = "" + numeradorA[7] + "/" + denominadorA[7]; }
                if (denominadorA[8] == 1 || numeradorA[8] == 0) { mb13.Text = "" + numero[8]; } else { mb13.Text = "" + numeradorA[8] + "/" + denominadorA[8]; }
                if (denominadorA[0] == 1 || numeradorA[0] == 0) { mb31.Text = "" + numero[0]; } else { mb31.Text = "" + numeradorA[0] + "/" + denominadorA[0]; }
                if (denominadorA[1] == 1 || numeradorA[1] == 0) { mb32.Text = "" + numero[1]; } else { mb32.Text = "" + numeradorA[1] + "/" + denominadorA[1]; }
                if (denominadorA[2] == 1 || numeradorA[2] == 0) { mb33.Text = "" + numero[2]; } else { mb33.Text = "" + numeradorA[2] + "/" + denominadorA[2]; }
                in11.Text = "" + 0; in12.Text = "" + 0; in13.Text = "" + 1;
                in31.Text = "" + 1; in32.Text = "" + 0; in33.Text = "" + 0;
                cambio = true;
            }
            if (numero[4] == 0 && numero[1] != 0 && cambio == false)
            {
                if (denominadorA[3] == 1 || numeradorA[3] == 0) { mb11.Text = "" + numero[3]; } else { mb11.Text = "" + numeradorA[3] + "/" + denominadorA[3]; }
                if (denominadorA[4] == 1 || numeradorA[4] == 0) { mb12.Text = "" + numero[4]; } else { mb12.Text = "" + numeradorA[4] + "/" + denominadorA[4]; }
                if (denominadorA[5] == 1 || numeradorA[5] == 0) { mb13.Text = "" + numero[5]; } else { mb13.Text = "" + numeradorA[5] + "/" + denominadorA[5]; }
                if (denominadorA[0] == 1 || numeradorA[0] == 0) { mb21.Text = "" + numero[0]; } else { mb21.Text = "" + numeradorA[0] + "/" + denominadorA[0]; }
                if (denominadorA[1] == 1 || numeradorA[1] == 0) { mb22.Text = "" + numero[1]; } else { mb22.Text = "" + numeradorA[1] + "/" + denominadorA[1]; }
                if (denominadorA[2] == 1 || numeradorA[2] == 0) { mb23.Text = "" + numero[2]; } else { mb23.Text = "" + numeradorA[2] + "/" + denominadorA[2]; }
                in11.Text = "" + 0; in12.Text = "" + 1; in13.Text = "" + 0;
                in21.Text = "" + 1; in22.Text = "" + 0; in23.Text = "" + 0;
                cambio = true;
            }
            if (numero[4] == 0 && numero[7] != 0 && cambio == false)
            {
                if (denominadorA[6] == 1 || numeradorA[6] == 0) { mb21.Text = "" + numero[6]; } else { mb21.Text = "" + numeradorA[6] + "/" + denominadorA[6]; }
                if (denominadorA[7] == 1 || numeradorA[7] == 0) { mb22.Text = "" + numero[7]; } else { mb22.Text = "" + numeradorA[7] + "/" + denominadorA[7]; }
                if (denominadorA[8] == 1 || numeradorA[8] == 0) { mb23.Text = "" + numero[8]; } else { mb23.Text = "" + numeradorA[8] + "/" + denominadorA[8]; }
                if (denominadorA[3] == 1 || numeradorA[3] == 0) { mb31.Text = "" + numero[3]; } else { mb31.Text = "" + numeradorA[3] + "/" + denominadorA[3]; }
                if (denominadorA[4] == 1 || numeradorA[4] == 0) { mb32.Text = "" + numero[4]; } else { mb32.Text = "" + numeradorA[4] + "/" + denominadorA[4]; }
                if (denominadorA[5] == 1 || numeradorA[5] == 0) { mb33.Text = "" + numero[5]; } else { mb33.Text = "" + numeradorA[5] + "/" + denominadorA[5]; }
                in21.Text = "" + 0; in22.Text = "" + 0; in23.Text = "" + 1;
                in31.Text = "" + 0; in32.Text = "" + 1; in33.Text = "" + 0;
                cambio = true;
            }
            if (numero[8] == 0 && numero[5] != 0 && cambio == false)
            {
                if (denominadorA[6] == 1 || numeradorA[6] == 0) { mb21.Text = "" + numero[6]; } else { mb21.Text = "" + numeradorA[6] + "/" + denominadorA[6]; }
                if (denominadorA[7] == 1 || numeradorA[7] == 0) { mb22.Text = "" + numero[7]; } else { mb22.Text = "" + numeradorA[7] + "/" + denominadorA[7]; }
                if (denominadorA[8] == 1 || numeradorA[8] == 0) { mb23.Text = "" + numero[8]; } else { mb23.Text = "" + numeradorA[8] + "/" + denominadorA[8]; }
                if (denominadorA[3] == 1 || numeradorA[3] == 0) { mb31.Text = "" + numero[3]; } else { mb31.Text = "" + numeradorA[3] + "/" + denominadorA[3]; }
                if (denominadorA[4] == 1 || numeradorA[4] == 0) { mb32.Text = "" + numero[4]; } else { mb32.Text = "" + numeradorA[4] + "/" + denominadorA[4]; }
                if (denominadorA[5] == 1 || numeradorA[5] == 0) { mb33.Text = "" + numero[5]; } else { mb33.Text = "" + numeradorA[5] + "/" + denominadorA[5]; }
                in21.Text = "" + 0; in22.Text = "" + 0; in23.Text = "" + 1;
                in31.Text = "" + 0; in32.Text = "" + 1; in33.Text = "" + 0;
                cambio = true;
            }
            if (numero[8] == 0 && numero[2] != 0 && cambio == false)
            {
                if (denominadorA[6] == 1 || numeradorA[6] == 0) { mb11.Text = "" + numero[6]; } else { mb11.Text = "" + numeradorA[6] + "/" + denominadorA[6]; }
                if (denominadorA[7] == 1 || numeradorA[7] == 0) { mb12.Text = "" + numero[7]; } else { mb12.Text = "" + numeradorA[7] + "/" + denominadorA[7]; }
                if (denominadorA[8] == 1 || numeradorA[8] == 0) { mb13.Text = "" + numero[8]; } else { mb13.Text = "" + numeradorA[8] + "/" + denominadorA[8]; }
                if (denominadorA[0] == 1 || numeradorA[0] == 0) { mb31.Text = "" + numero[0]; } else { mb31.Text = "" + numeradorA[0] + "/" + denominadorA[0]; }
                if (denominadorA[1] == 1 || numeradorA[1] == 0) { mb32.Text = "" + numero[1]; } else { mb32.Text = "" + numeradorA[1] + "/" + denominadorA[1]; } 
                if (denominadorA[2] == 1 || numeradorA[2] == 0) { mb33.Text = "" + numero[2]; } else { mb33.Text = "" + numeradorA[2] + "/" + denominadorA[2]; }
                in11.Text = "" + 0; in12.Text = "" + 0; in13.Text = "" + 1;
                in31.Text = "" + 1; in32.Text = "" + 0; in33.Text = "" + 0;
                cambio = true;
            }

            for (i = 0; i < 18; i++)
            {
                if (i < 9)
                {
                    matrizA[i] = cajas2.ElementAt(i).Text;
                    fraccionesA(i);
                }
                else
                {
                    matrizA[i] = cajas3.ElementAt(i-9).Text;
                    fraccionesA(i);
                }
                
                //MessageBox.Show("" + numero[i]);
            }

            string ecuacion;
            int j;
            double num, den; 

            /*if (numero[0] != 1)
            {
                if (denominadorA[0] == 1 || numeradorA[0] == 0)
                {
                    ecuacion = "F1 = F1 /" + numero[0];
                }
                else
                {
                    ecuacion = "F1 = F1 / " + numeradorA[0] + "/" + denominadorA[0];
                }
                MessageBox.Show(ecuacion);
                double auxNum = numeradorA[0];
                double auxDen = denominadorA[0];
                
                for (j = 0; j <= 2; j++)
                {
                    //MessageBox.Show("" + numeradorA[j] + "" + denominadorA[j]);                    
                    cajas2.ElementAt(j).Text = "" + numeradorA[j] * auxDen + "/" + denominadorA[j] * auxNum;
                    cajas3.ElementAt(j).Text = "" + numeradorA[j+9] * auxDen + "/" + denominadorA[j+9] * auxNum;
                    matrizA[j] = cajas2.ElementAt(j).Text;
                    matrizA[j + 9] = cajas3.ElementAt(j).Text;
                    fraccionesA(j);
                    fraccionesA(j + 9);
                    simplificar(j);
                    simplificar(j + 9);
                    if (denominadorA[j] == 1 || numeradorA[j] == 0 || numeradorA[j] == denominadorA[j])
                    {
                        cajas2.ElementAt(j).Text = "" + numero[j];
                    }
                    else
                    {
                        cajas2.ElementAt(j).Text = "" + numeradorA[j] + "/" + denominadorA[j];
                    }
                    if (denominadorA[j + 9] == 1 || numeradorA[j + 9] == 0 || numeradorA[j + 9] == denominadorA[j + 9])
                    {
                        cajas3.ElementAt(j).Text = "" + numero[j+9];
                    }
                    else
                    {
                        cajas3.ElementAt(j).Text = "" + numeradorA[j+9] + "/" + denominadorA[j+9];
                    }
                }
            }*/
            double n, d;
            convierteUno(0, "F1");
            convierteCero(3);
            convierteCero(6);

            convierteUno(4, "F2");
            convierteCero(1);
            convierteCero(7);

            /*convierteUno(8, "F3");
            convierteCero(3, 5);
            convierteCero(6, 8);*/
            /*if (numero[3] != 0)
            {
                if (numero[3] > 0) { n = - numeradorA[3]; }
                else { n = numeradorA[3]; }
                d = denominadorA[3];
                MessageBox.Show("" + n);
                //MessageBox.Show("" + numeradorA[0] + "/" + denominadorA[0]);
                for (j = 3; j <= 5; j++)
                {
                    num = n * numeradorA[j - 3];
                    den = d * denominadorA[j - 3];
                    MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j - 3] + "/" + denominadorA[j - 3] + ")","Matriz Identidad");
                    numeradorA[j] = (numeradorA[j] * den) + (denominadorA[j] * num);
                    denominadorA[j] = denominadorA[j] * den;
                    simplificar(j);
                    if (denominadorA[j] == 1 || numeradorA[j] == 0)
                    {
                        cajas2.ElementAt(j).Text = "" + numero[j];
                    }
                    else
                    {
                        cajas2.ElementAt(j).Text = "" + numeradorA[j] + "/" + denominadorA[j];
                    }

                    num = n * numeradorA[(j - 3)+9];
                    den = d * denominadorA[(j - 3)+9];
                    MessageBox.Show("" + numeradorA[j+9] + "/" + denominadorA[j+9] + " " + n + "/" + d + "(" + numeradorA[(j - 3)+9] + "/" + denominadorA[(j - 3)+9] + ")","Matriz Inversa");
                    numeradorA[j+9] = (numeradorA[j+9] * den) + (denominadorA[j+9] * num);
                    denominadorA[j+9] = denominadorA[j+9] * den;
                    simplificar(j+9);                    
                    if (denominadorA[j+9] == 1 || numeradorA[j+9] == 0)
                    {
                        cajas3.ElementAt(j).Text = "" + numero[j+9];
                    }
                    else
                    {
                        cajas3.ElementAt(j).Text = "" + numeradorA[j+9] + "/" + denominadorA[j+9];
                    }                                    
                }
            }*/          
        }
        private void convierteUno(int a, string f)
        {
            string ecuacion;
            int j;
            int b = 0, c = 0;
            if (numero[a] != 1)
            {
                //MessageBox.Show("bla " + numeradorA[a] + "/" + denominadorA[a]);
                if (denominadorA[a] == 1 || numeradorA[a] == 0 || numeradorA[a]==denominadorA[a])
                {
                    ecuacion = "" + f + " = " + f + " / " + numero[a];
                }
                else
                {
                    ecuacion = "" + f + " = " + f + " /  " + numeradorA[a] + "/" + denominadorA[a];
                }
                MessageBox.Show(ecuacion);
                double auxNum = numeradorA[a];
                double auxDen = denominadorA[a];

                if (a == 0) { b = 2; c = 11; }
                if (a == 4) { b = 5; c = 14; }
                if (a == 8) { b = 8; c = 17; }

                for (j = a; j <= b; j++)
                {
                    //MessageBox.Show("" + numeradorA[j] + "" + denominadorA[j]);                    
                    cajas2.ElementAt(j).Text = "" + numeradorA[j] * auxDen + "/" + denominadorA[j] * auxNum;
                    matrizA[j] = cajas2.ElementAt(j).Text;
                    fraccionesA(j);
                    simplificar(j);
                    if (denominadorA[j] == 1 || numeradorA[j] == 0 || numeradorA[j] == denominadorA[j])
                    {
                        cajas2.ElementAt(j).Text = "" + numero[j];
                    }
                    else
                    {
                        cajas2.ElementAt(j).Text = "" + numeradorA[j] + "/" + denominadorA[j];
                    }
                }
                int z = a;
                int aux = 0;
                if (a == 0) { aux = a + 9; }
                if (a == 4) { aux = a + 8; }
                if (a == 8) { aux = a + 7; }
                for (j = aux; j <= c; j++)
                {
                    //MessageBox.Show("" + numeradorA[j] + "" + denominadorA[j]);                    
                    cajas3.ElementAt(z).Text = "" + numeradorA[j] * auxDen + "/" + denominadorA[j] * auxNum;
                    matrizA[j] = cajas3.ElementAt(z).Text;
                    fraccionesA(j);
                    simplificar(j);
                    if (denominadorA[j] == 1 || numeradorA[j] == 0 || numeradorA[j] == denominadorA[j])
                    {
                        cajas3.ElementAt(z).Text = "" + numero[j];
                    }
                    else
                    {
                        cajas3.ElementAt(z).Text = "" + numeradorA[j] + "/" + denominadorA[j];
                    }
                    z++;
                }
            }
        }
        private void convierteCero(int a)
        {
            int j;
            double num=0, den=0;
            double n=0, d;
            int b = 0, c = 0;
            if (numero[a] != 0)
            {
                /*if (numero[a] > 0) { n = numeradorA[a]*(-1); }
                else if(numero[a] < 0){ n = numeradorA[a]; }*/
                if (a == 1 || a == 2) { b = 2; c = 11; }
                if (a == 3 || a == 5) { b = 5; c = 14; }
                if (a == 6 || a == 7) { b = 8; c = 17; }
                n = -numeradorA[a];
                d = denominadorA[a];
                MessageBox.Show("" + a);
                //MessageBox.Show("" + numeradorA[0] + "/" + denominadorA[0]);
                for (j = a; j <= b; j++)
                {
                    if (a == 3 || a == 6)
                    {
                        num = n * numeradorA[j - a];
                        den = d * denominadorA[j - a];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j - a] + "/" + denominadorA[j - a] + ")", "Matriz Identidad");
                    }
                    if (a == 1 || a == 5)
                    {
                        MessageBox.Show("" + (j + 3));
                        num = n * numeradorA[j + 3];
                        den = d * denominadorA[j + 3];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j + 3] + "/" + denominadorA[j + 3] + ")", "Matriz Identidad");
                    }
                    if (a == 2)
                    {
                        num = n * numeradorA[j + 6];
                        den = d * denominadorA[j + 6];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j + 6] + "/" + denominadorA[j + 6] + ")", "Matriz Identidad");
                    }
                    if (a == 7)
                    {
                        num = n * numeradorA[j - 3];
                        den = d * denominadorA[j - 3];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j - 3] + "/" + denominadorA[j - 3] + ")", "Matriz Identidad");
                    }
                    
                    numeradorA[j] = (numeradorA[j] * den) + (denominadorA[j] * num);
                    denominadorA[j] = denominadorA[j] * den;
                    simplificar(j);
                    if (denominadorA[j] == 1 || numeradorA[j] == 0)
                    {
                        cajas2.ElementAt(j).Text = "" + numero[j];
                    }
                    else
                    {
                        cajas2.ElementAt(j).Text = "" + numeradorA[j] + "/" + denominadorA[j];
                    }
                    matrizA[j] = cajas1.ElementAt(j).Text;
                    fraccionesA(j);
                }
                int z = a;
                int aux=0;
                if (a == 3 || a == 6) { aux = a + 9; }
                if (a == 1 || a == 7) { aux = a + 8; }
                if (a == 2 || a == 5) { aux = a + 7; }
                for (j = aux; j <= c; j++)
                {
                    if (a == 3 || a == 6)
                    {
                        num = n * numeradorA[(j - a)];
                        den = d * denominadorA[(j - a)];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[(j - a)] + "/" + denominadorA[(j - a)] + ")", "Matriz Inversa");
                    }
                    if (a == 1 || a == 5)
                    {
                        num = n * numeradorA[j + 3];
                        den = d * denominadorA[j + 3];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j + 3] + "/" + denominadorA[j + 3] + ")", "Matriz Inversa");
                    }
                    if (a == 2)
                    {
                        num = n * numeradorA[j + 6];
                        den = d * denominadorA[j + 6];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j + 6] + "/" + denominadorA[j + 6] + ")", "Matriz Identidad");
                    }
                    if (a == 7)
                    {
                        num = n * numeradorA[j - 3];
                        den = d * denominadorA[j - 3];
                        MessageBox.Show("" + numeradorA[j] + "/" + denominadorA[j] + " " + n + "/" + d + "(" + numeradorA[j - 3] + "/" + denominadorA[j - 3] + ")", "Matriz Inversa");
                    }
                    
                    numeradorA[j] = (numeradorA[j] * den) + (denominadorA[j] * num);
                    denominadorA[j] = denominadorA[j] * den;
                    simplificar(j);
                    if (denominadorA[j] == 1 || numeradorA[j] == 0)
                    {
                        cajas3.ElementAt(z).Text = "" + numero[j];
                    }
                    else
                    {
                        cajas3.ElementAt(z).Text = "" + numeradorA[j] + "/" + denominadorA[j];
                    }
                    matrizA[j] = cajas1.ElementAt(z).Text;
                    fraccionesA(j);
                    z++;
                }
            }
        }

        private void convierte_btn_Click(object sender, EventArgs e)
        {           
            gaussJordan();
        }
    }
}
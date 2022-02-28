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
    public partial class A : Form
    {
        
        public A()
        {
            InitializeComponent();
        }

        public double[] numeradorA = new double[10];
        public double[] denominadorA = new double[10];
        public string[] matrizA = new string[10];
        List<Label> cajas = new List<Label>();
        string modo = "Fraccion";
        private void button1_Click(object sender, EventArgs e)
        {
            if(escA.Text=="")
            {
                MessageBox.Show("Escalar no puede ser vacio", "Invalido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                fraccion_btn.Enabled = false;
                decimal_btn.Enabled = true;
                this.matrizA[9] = escA.Text;
                for (int i = 0; i < 10; i++)
                {
                    fraccionesA(i);
                }
                //MessageBox.Show("" + this.numeradorA[9] + "/" + this.denominadorA[9]);
                EscalarA();
                Modo();
            }
        }

        private void EscalarA_Load(object sender, EventArgs e)
        {
            escA.Focus();
            this.matrizA[0] = ea11.Text;
            this.matrizA[1] = ea12.Text;
            this.matrizA[2] = ea13.Text;
            this.matrizA[3] = ea21.Text;
            this.matrizA[4] = ea22.Text;
            this.matrizA[5] = ea23.Text;
            this.matrizA[6] = ea31.Text;
            this.matrizA[7] = ea32.Text;
            this.matrizA[8] = ea33.Text;

            cajas.Add(rea11);
            cajas.Add(rea12);
            cajas.Add(rea13);
            cajas.Add(rea21);
            cajas.Add(rea22);
            cajas.Add(rea23);
            cajas.Add(rea31);
            cajas.Add(rea32);
            cajas.Add(rea33);

            fraccion_btn.Enabled = false;
            decimal_btn.Enabled = false;


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
            //MessageBox.Show(""+a);

            numeradorConPunto(numeradorA[a], denominadorA[a], a, 'A');
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
                this.numeradorA[indice] = numerador;
                this.denominadorA[indice] = denominador;
            }
        }
        double[] numero = new double[9];
        double[] nume = new double[9];
        double[] deno = new double[9];

        private void EscalarA()
        {
            int i;
            for (i = 0; i < 9; i++)
            {
                nume[i] = numeradorA[9] * numeradorA[i];
                deno[i] = denominadorA[9] * denominadorA[i];
                numero[i] = nume[i] / deno[i];
                //MessageBox.Show(""+nume[i]+"/"+deno[i]+"="+numero[i]);
                for (int j = 2; j < 20; j++)
                {
                    do
                    {
                        if (nume[i] % j == 0 && deno[i] % j == 0)
                        {
                            nume[i] = nume[i] / j;
                            deno[i] = deno[i] / j;
                        }
                        else
                        {
                            break;
                        }
                    } while (nume[i] > 1 && deno[i] > 1);
                }
                numero[i] = nume[i] / deno[i];
            }

            
        }
        private void Modo()
        {
            for (int i = 0; i < 9; i++)
            {
                if (modo == "Fraccion")
                {
                    if(deno[i]==1|| deno[i]==nume[i])
                    {
                        cajas.ElementAt(i).Text = this.numero[i].ToString();
                    }
                    else
                    {
                        cajas.ElementAt(i).Text = this.nume[i].ToString() + "/" + this.deno[i].ToString();
                    }

                }
                else
                {
                    cajas.ElementAt(i).Text = this.numero[i].ToString();
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void escA_KeyPress(object sender, KeyPressEventArgs e)
        {
            validacion v = new validacion();
            v.valida(e, escA);
        }

        private void fraccion_btn_Click(object sender, EventArgs e)
        {
            fraccion_btn.Enabled = false;
            decimal_btn.Enabled = true;
            modo = "Fraccion";
            Modo();
            
        }

        private void decimal_btn_Click(object sender, EventArgs e)
        {
            decimal_btn.Enabled = false;
            fraccion_btn.Enabled = true;
            modo = "Decimal";
            Modo();
        }




    }
}

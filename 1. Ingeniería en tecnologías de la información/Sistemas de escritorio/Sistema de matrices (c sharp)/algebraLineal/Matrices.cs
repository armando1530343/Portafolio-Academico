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
    
    public partial class Matrices : Form
    {
        validacion v = new validacion();

        public Matrices()
        {
            InitializeComponent();
        }

        public double[] numeradorA = new double[9];
        public double[] denominadorA = new double[9];
        public double[] numeradorB = new double[9];
        public double[] denominadorB = new double[9];
        public string[] matrizA = new string[9];
        public string[] matrizB = new string[9];

        double numDet, denDet;

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

        private double determinante(char c)
        {
            double[] detNum = new double[3];
            double[] detDen = new double[3];
            //double numDet, denDet;
            double num1, num2, den1, den2, numerador, denominador;
            double numero;
            num1 = this.numeradorA[4] * this.numeradorA[8];
            den1 = this.denominadorA[4] * this.denominadorA[8];
            num2 = this.numeradorA[7] * this.numeradorA[5];
            den2 = this.denominadorA[7] * this.denominadorA[5];
            numerador = (num1 * den2) - (den1 * num2);
            denominador = den1 * den2;
            detNum[0] = this.numeradorA[0] * numerador;
            detDen[0] = this.denominadorA[0] * denominador;

            num1 = this.numeradorA[3] * this.numeradorA[8];
            den1 = this.denominadorA[3] * this.denominadorA[8];
            num2 = this.numeradorA[6] * this.numeradorA[5];
            den2 = this.denominadorA[6] * this.denominadorA[5];
            numerador = (num1 * den2) - (den1 * num2);
            denominador = den1 * den2;
            detNum[1] = (-1 * this.numeradorA[1]) * numerador;
            detDen[1] = this.denominadorA[1] * denominador;

            num1 = this.numeradorA[3] * this.numeradorA[7];
            den1 = this.denominadorA[3] * this.denominadorA[7];
            num2 = this.numeradorA[6] * this.numeradorA[4];
            den2 = this.denominadorA[6] * this.denominadorA[4];
            numerador = (num1 * den2) - (den1 * num2);
            denominador = den1 * den2;
            detNum[2] = this.numeradorA[2] * numerador;
            detDen[2] = this.denominadorA[2] * denominador;

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

            if (denDet == 1 || numDet == 0)
            {
                MessageBox.Show("Determinante de " + c + " = " + numero);
            }
            else
            {
                MessageBox.Show("Determinante de " + c + " = " + numDet + "/" + denDet);
            }
            return numero;
        }

        private void cerrar_btn_Click_1(object sender, EventArgs e)
        {
            this.Close();
        }
        public void borrarCajas()
        {
            a11.Text = ""; b11.Text = "";
            a12.Text = ""; b12.Text = "";
            a13.Text = ""; b13.Text = "";
            a21.Text = ""; b21.Text = "";
            a22.Text = ""; b22.Text = "";
            a23.Text = ""; b23.Text = "";
            a31.Text = ""; b31.Text = "";
            a32.Text = ""; b32.Text = "";
            a33.Text = ""; b33.Text = "";
            a11.Focus();
        }

        public void cajasVacias(int i)
        {

            if (a11.Text == "" || a12.Text == "" || a13.Text == ""||
                a21.Text == "" || a22.Text == "" || a23.Text == ""||
                a31.Text == "" || a32.Text == "" || a33.Text == ""||
                b11.Text == "" || b12.Text == "" || b13.Text == ""||
                b21.Text == "" || b22.Text == "" || b23.Text == ""||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("No pueden quedar cajas vacias", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
            else
            {
                Operaciones1 op = new Operaciones1(i);

                //pasa la informacion de las cajas de las matrices al otro formulario
                op.ma11.Text = a11.Text; op.mb11.Text = b11.Text;
                op.ma12.Text = a12.Text; op.mb12.Text = b12.Text;
                op.ma13.Text = a13.Text; op.mb13.Text = b13.Text;
                op.ma21.Text = a21.Text; op.mb21.Text = b21.Text;
                op.ma22.Text = a22.Text; op.mb22.Text = b22.Text;
                op.ma23.Text = a23.Text; op.mb23.Text = b23.Text;
                op.ma31.Text = a31.Text; op.mb31.Text = b31.Text;
                op.ma32.Text = a32.Text; op.mb32.Text = b32.Text;
                op.ma33.Text = a33.Text; op.mb33.Text = b33.Text;
                
                op.Show();                
            }            
        }

        private void Matrices_Load(object sender, EventArgs e)
        {
            inicio();
        }
        public void inicio()
        {
            a11.Focus();
        }

        private void restaAB_Click(object sender, EventArgs e)
        {
            cajasVacias(2);
        }

        private void a11_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a11);
        }

        private void a12_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a12);
        }

        private void a13_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a13);
        }

        private void a21_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a21);
        }

        private void a22_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a22);
        }

        private void a23_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a23);
        }

        private void a31_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a31);
        }

        private void a32_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a32);
        }

        private void a33_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, a33);
        }

        private void restaBA_Click(object sender, EventArgs e)
        {
            cajasVacias(3);
        }

        private void multiAB_Click(object sender, EventArgs e)
        {
            cajasVacias(4);
        }

        private void multiBA_Click(object sender, EventArgs e)
        {
            cajasVacias(5);
        }

        public void sumaAB_Click(object sender, EventArgs e)
        {
            cajasVacias(1);
        }

        private void limpia_btn_Click(object sender, EventArgs e)
        {
            borrarCajas();
        }

        private void identidad_Click(object sender, EventArgs e)
        {
            if(a11.Text == "" || a12.Text == "" || a13.Text == "" ||
               a21.Text == "" || a22.Text == "" || a23.Text == "" ||
               a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Matriz A incompleta", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                int i;
                matrizA[0] = a11.Text;
                matrizA[1] = a12.Text;
                matrizA[2] = a13.Text;
                matrizA[3] = a21.Text;
                matrizA[4] = a22.Text;
                matrizA[5] = a23.Text;
                matrizA[6] = a31.Text;
                matrizA[7] = a32.Text;
                matrizA[8] = a33.Text;
                for (i = 0; i < 9; i++)
                {
                    fraccionesA(i);
                }
                determinante('A');

                if (numDet / denDet == 0)
                {
                    MessageBox.Show("La matriz es Invertible");
                }
                else
                {
                    MatrizIdentidad mI = new MatrizIdentidad();
                    mI.m11.Text = a11.Text;
                    mI.m12.Text = a12.Text;
                    mI.m13.Text = a13.Text;
                    mI.m21.Text = a21.Text;
                    mI.m22.Text = a22.Text;
                    mI.m23.Text = a23.Text;
                    mI.m31.Text = a31.Text;
                    mI.m32.Text = a32.Text;
                    mI.m33.Text = a33.Text;
                    mI.Show();
                }               
            }
        }
        public void limpiaMatrizA()
        {

        }

        private void b11_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b11);
        }

        private void b12_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b12);
        }

        private void b13_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b13);
        }

        private void b21_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b21);
        }

        private void b22_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b22);
        }

        private void b23_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b23);
        }

        private void b31_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b31);
        }

        private void b32_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b32);
        }

        private void b33_KeyPress(object sender, KeyPressEventArgs e)
        {
            v.valida(e, b33);
        }
        
        private void escA_Click(object sender, EventArgs e)
        {
            
            if (a11.Text == "" || a12.Text == "" || a13.Text == ""||
                a21.Text == "" || a22.Text == "" || a23.Text == ""||
                a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Cajas vacias", "invalido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                A escalar = new A();
                escalar.ea11.Text = a11.Text;
                escalar.ea12.Text = a12.Text;
                escalar.ea13.Text = a13.Text;
                escalar.ea21.Text = a21.Text;
                escalar.ea22.Text = a22.Text;
                escalar.ea23.Text = a23.Text;
                escalar.ea31.Text = a31.Text;
                escalar.ea32.Text = a32.Text;
                escalar.ea33.Text = a33.Text;
                escalar.Show();
            }
        }

        private void escB_Click(object sender, EventArgs e)
        {
            if (b11.Text == "" || b12.Text == "" || b13.Text == "" ||
                b21.Text == "" || b22.Text == "" || b23.Text == "" ||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("Cajas vacias", "invalido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                A escalar = new A();
                escalar.ea11.Text = b11.Text;
                escalar.ea12.Text = b12.Text;
                escalar.ea13.Text = b13.Text;
                escalar.ea21.Text = b21.Text;
                escalar.ea22.Text = b22.Text;
                escalar.ea23.Text = b23.Text;
                escalar.ea31.Text = b31.Text;
                escalar.ea32.Text = b32.Text;
                escalar.ea33.Text = b33.Text;
                escalar.Show();
            }
        }

        private void detA_Click(object sender, EventArgs e)
        {
            int i;
            if (a11.Text == "" || a12.Text == "" || a13.Text == "" ||
                a21.Text == "" || a22.Text == "" || a23.Text == "" ||
                a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz A", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                matrizA[0] = a11.Text;
                matrizA[1] = a12.Text;
                matrizA[2] = a13.Text;
                matrizA[3] = a21.Text;
                matrizA[4] = a22.Text;
                matrizA[5] = a23.Text;
                matrizA[6] = a31.Text;
                matrizA[7] = a32.Text;
                matrizA[8] = a33.Text;
                for (i = 0; i < 9; i++)
                {
                    fraccionesA(i);
                }
                determinante('A');
            }           
        }
        private void detB_Click(object sender, EventArgs e)
        {
            int i;
            if (b11.Text == "" || b12.Text == "" || b13.Text == ""||
                b21.Text == "" || b22.Text == "" || b23.Text == ""||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz B","Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                matrizA[0] = b11.Text;
                matrizA[1] = b12.Text;
                matrizA[2] = b13.Text;
                matrizA[3] = b21.Text;
                matrizA[4] = b22.Text;
                matrizA[5] = b23.Text;
                matrizA[6] = b31.Text;
                matrizA[7] = b32.Text;
                matrizA[8] = b33.Text;
                for (i = 0; i < 9; i++)
                {
                    fraccionesA(i);
                }
                determinante('B');
            }
            
        }

        private void adjA_Click(object sender, EventArgs e)
        {
            int i;
            if (a11.Text == "" || a12.Text == "" || a13.Text == "" ||
                a21.Text == "" || a22.Text == "" || a23.Text == "" ||
                a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz A", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Operaciones2 op2 = new Operaciones2(3);
                op2.mat11.Text = a11.Text;
                op2.mat12.Text = a12.Text;
                op2.mat13.Text = a13.Text;
                op2.mat21.Text = a21.Text;
                op2.mat22.Text = a22.Text;
                op2.mat23.Text = a23.Text;
                op2.mat31.Text = a31.Text;
                op2.mat32.Text = a32.Text;
                op2.mat33.Text = a33.Text;
                op2.Show();
            }
        }

        private void adjB_Click(object sender, EventArgs e)
        {
            int i;
            if (b11.Text == "" || b12.Text == "" || b13.Text == "" ||
                b21.Text == "" || b22.Text == "" || b23.Text == "" ||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz B", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Operaciones2 op2 = new Operaciones2(4);
                op2.mat11.Text = b11.Text;
                op2.mat12.Text = b12.Text;
                op2.mat13.Text = b13.Text;
                op2.mat21.Text = b21.Text;
                op2.mat22.Text = b22.Text;
                op2.mat23.Text = b23.Text;
                op2.mat31.Text = b31.Text;
                op2.mat32.Text = b32.Text;
                op2.mat33.Text = b33.Text;
                op2.Show();
            }
        }

        private void invA_Click(object sender, EventArgs e)
        {
            int i;
            double det=0;
            if (a11.Text == "" || a12.Text == "" || a13.Text == "" ||
                a21.Text == "" || a22.Text == "" || a23.Text == "" ||
                a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz A", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                matrizA[0] = a11.Text;
                matrizA[1] = a12.Text;
                matrizA[2] = a13.Text;
                matrizA[3] = a21.Text;
                matrizA[4] = a22.Text;
                matrizA[5] = a23.Text;
                matrizA[6] = a31.Text;
                matrizA[7] = a32.Text;
                matrizA[8] = a33.Text;
                for (i = 0; i < 9; i++)
                {
                    fraccionesA(i);
                }
                det = determinante('A');
                Operaciones2 op2 = new Operaciones2(1);
                op2.mat11.Text = a11.Text;
                op2.mat12.Text = a12.Text;
                op2.mat13.Text = a13.Text;
                op2.mat21.Text = a21.Text;
                op2.mat22.Text = a22.Text;
                op2.mat23.Text = a23.Text;
                op2.mat31.Text = a31.Text;
                op2.mat32.Text = a32.Text;
                op2.mat33.Text = a33.Text;
                
                if (det != 0)
                {
                    op2.Show();
                }
                else { MessageBox.Show("Es Invertible"); }

                
            }
        }

        private void invB_Click(object sender, EventArgs e)
        {
            int i;
            double det = 0;
            if (b11.Text == "" || b12.Text == "" || b13.Text == "" ||
                b21.Text == "" || b22.Text == "" || b23.Text == "" ||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz B", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                det = determinante('A');
                Operaciones2 op2 = new Operaciones2(2);
                op2.mat11.Text = b11.Text;
                op2.mat12.Text = b12.Text;
                op2.mat13.Text = b13.Text;
                op2.mat21.Text = b21.Text;
                op2.mat22.Text = b22.Text;
                op2.mat23.Text = b23.Text;
                op2.mat31.Text = b31.Text;
                op2.mat32.Text = b32.Text;
                op2.mat33.Text = b33.Text;
                if (det != 0)
                {
                    op2.Show();
                }
                else { MessageBox.Show("Es Invertible"); }
                
                
                
            }
        }

        private void invertibleA_Click(object sender, EventArgs e)
        {
            int i;
            double det;
            if (a11.Text == "" || a12.Text == "" || a13.Text == "" ||
                a21.Text == "" || a22.Text == "" || a23.Text == "" ||
                a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz A", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                matrizA[0] = a11.Text;
                matrizA[1] = a12.Text;
                matrizA[2] = a13.Text;
                matrizA[3] = a21.Text;
                matrizA[4] = a22.Text;
                matrizA[5] = a23.Text;
                matrizA[6] = a31.Text;
                matrizA[7] = a32.Text;
                matrizA[8] = a33.Text;
                for (i = 0; i < 9; i++)
                {
                    fraccionesA(i);
                }
                det = determinante('A');
                if (det != 0)
                {
                    MessageBox.Show("True");
                }
                else { MessageBox.Show("False"); }
            }
        }

        private void invertibleB_Click(object sender, EventArgs e)
        {
            int i;
            double det;
            if (b11.Text == "" || b12.Text == "" || b13.Text == "" ||
                b21.Text == "" || b22.Text == "" || b23.Text == "" ||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz B", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                matrizA[0] = b11.Text;
                matrizA[1] = b12.Text;
                matrizA[2] = b13.Text;
                matrizA[3] = b21.Text;
                matrizA[4] = b22.Text;
                matrizA[5] = b23.Text;
                matrizA[6] = b31.Text;
                matrizA[7] = b32.Text;
                matrizA[8] = b33.Text;
                for (i = 0; i < 9; i++)
                {
                    fraccionesA(i);
                }
                det = determinante('B');
                if (det != 0)
                {
                    MessageBox.Show("True");
                }
                else { MessageBox.Show("False"); }
            }
        }

        private void At_Click(object sender, EventArgs e)
        {
            int i;
            double det;
            if (a11.Text == "" || a12.Text == "" || a13.Text == "" ||
                a21.Text == "" || a22.Text == "" || a23.Text == "" ||
                a31.Text == "" || a32.Text == "" || a33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz A", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Operaciones2 op2 = new Operaciones2(5);
                op2.mat11.Text = a11.Text;
                op2.mat12.Text = a12.Text;
                op2.mat13.Text = a13.Text;
                op2.mat21.Text = a21.Text;
                op2.mat22.Text = a22.Text;
                op2.mat23.Text = a23.Text;
                op2.mat31.Text = a31.Text;
                op2.mat32.Text = a32.Text;
                op2.mat33.Text = a33.Text;

                op2.op11.Text = a11.Text;
                op2.op12.Text = a21.Text;
                op2.op13.Text = a31.Text;
                op2.op21.Text = a12.Text;
                op2.op22.Text = a22.Text;
                op2.op23.Text = a32.Text;
                op2.op31.Text = a13.Text;
                op2.op32.Text = a23.Text;
                op2.op33.Text = a33.Text;
                op2.Show();
            }
        }

        private void Bt_Click(object sender, EventArgs e)
        {
            int i;
            double det;
            if (b11.Text == "" || b12.Text == "" || b13.Text == "" ||
                b21.Text == "" || b22.Text == "" || b23.Text == "" ||
                b31.Text == "" || b32.Text == "" || b33.Text == "")
            {
                MessageBox.Show("Cajas Vacias de la matriz B", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Operaciones2 op2 = new Operaciones2(6);
                op2.mat11.Text = b11.Text;
                op2.mat12.Text = b12.Text;
                op2.mat13.Text = b13.Text;
                op2.mat21.Text = b21.Text;
                op2.mat22.Text = b22.Text;
                op2.mat23.Text = b23.Text;
                op2.mat31.Text = b31.Text;
                op2.mat32.Text = b32.Text;
                op2.mat33.Text = b33.Text;

                op2.op11.Text = b11.Text;
                op2.op12.Text = b21.Text;
                op2.op13.Text = b31.Text;
                op2.op21.Text = b12.Text;
                op2.op22.Text = b22.Text;
                op2.op23.Text = b32.Text;
                op2.op31.Text = b13.Text;
                op2.op32.Text = b23.Text;
                op2.op33.Text = b33.Text;
                op2.Show();
            }
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }                      
    }
}

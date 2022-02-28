using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace algebraLineal
{
    class Metodos
    {
        /*double[] numeradorA = new double[9];
        double[] denominadorA = new double[9];
        double[] numeradorB = new double[9];
        double[] denominadorB = new double[9];
        string[] matrizA = new string[9];
        string[] matrizB = new string[9];*/
        Operaciones1 op1;

        public void fracciones(int a, char ab)
        {
            
            string matriz;
            double numerador, denominador;
            
            if (ab == 'A')
            {
                matriz = op1.matrizA[a];
                numerador = op1.numeradorA[a];
                denominador = op1.denominadorA[a];
            }
            else
            {
                matriz = op1.matrizB[a];
                numerador = op1.numeradorB[a];
                denominador = op1.denominadorB[a];
            }
            
            string string1 = "";
            string string2 = "";
            int i, aux = 0;
            bool division = false;
            for (i = 0; i < op1.matrizA[a].Length; i++)
            {
                if (op1.matrizA[a].ElementAt(i) != '/')
                {
                    string1 = string1 + op1.matrizA[a].ElementAt(i);
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
                for (i = aux; i < op1.matrizA[a].Length; i++)
                {
                    string2 = string2 + op1.matrizA[a].ElementAt(i);
                }
            }
            else
            {
                string2 = "1";
            }
            //int.TryParse(stringA, out numeradorA[a]);           
            op1.numeradorA[a] = double.Parse(string1);
            op1.denominadorA[a] = double.Parse(string2);

            //numeradorConPunto(op1.numeradorA[a], op1.denominadorA[a], a, ab);
        }
        /*public void numeradorConPunto(double numerador, double denominador, int indice, char AB)
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
                    op1.numeradorA[indice] = numerador;
                    op1.denominadorA[indice] = denominador;
                }
                else
                {
                    op1.numeradorB[indice] = numerador;
                    op1.denominadorB[indice] = denominador;
                }
            }
        }*/
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace algebraLineal
{
    class validacion
    {
        
        public void valida(KeyPressEventArgs e, TextBox texto)
        {
            string cadena = texto.Text;
            int i;
            //de acuerdo al codigo ASCII de cada caracter
            // 32=espacio  8=retroceso  
            
            if (e.KeyChar == 32 || e.KeyChar == 8 || e.KeyChar == '/' || e.KeyChar == '-' || e.KeyChar == '.')
            {
                if (cadena.Length == 0 && e.KeyChar == '/')
                {
                    e.Handled = true;
                }
                else
                {
                    for (i = 0; i < cadena.Length; i++)
                    {

                        if (e.KeyChar == '/')
                        {
                            if (cadena.ElementAt(i) == '/')
                            {
                                e.Handled = true;
                            }
                            if (cadena.ElementAt(i) == '.')
                            {
                                e.Handled = true;
                                MessageBox.Show("no puede ser fraccion", "Restriccion", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            }
                        }
                        else if (e.KeyChar == '.')
                        {
                            
                            if (cadena.ElementAt(i) == '.')
                            {
                                e.Handled = true;
                            }
                            if (cadena.ElementAt(i) == '/')
                            {
                                e.Handled = true;
                                MessageBox.Show("no puede haber decimales", "Restriccion", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            }
                        }
                    }
                }
                //e.Handled = false;
            }
            else if(char.IsNumber(e.KeyChar))
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }
    }
}

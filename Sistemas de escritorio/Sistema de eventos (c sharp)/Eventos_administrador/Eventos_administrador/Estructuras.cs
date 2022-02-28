using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Windows.Forms;
using System.Drawing;

namespace Eventos_administrador
{
    class Estructuras
    {
        WebBrowser navegador;
        Agregar_evento ae;
        TextBox nombre, lugar, fecha, descripcion, asistentes;

        public Estructuras(WebBrowser nav, TextBox nom, TextBox lug, TextBox fec, TextBox des, TextBox asis)//(WebBrowser nav)
        {
            navegador = nav;
            nombre = nom;
            lugar = lug;
            fecha = fec;
            descripcion = des;
            asistentes = asis;
        }
        public void el_vortex()
        {
            string asist="";
            string fec = "";

            nombre.Text = navegador.Document.GetElementById("seo_h1_tag").InnerText;
            foreach (HtmlElement elemento in navegador.Document.All)
            {
                if (elemento.GetAttribute("classname").Contains("_5xhp fsm fwn fcg"))
                {
                    lugar.Text = elemento.InnerText;
                }
                if (elemento.GetAttribute("classname").Contains("_publicProdFeedInfo__timeRowTitle _5xhk"))
                {
                    fec = elemento.InnerText;
                }
                if (elemento.GetAttribute("classname").Contains("_5z74"))
                {
                    asist = elemento.InnerText;
                }
                if (elemento.GetAttribute("data-testid").Contains("event-permalink-details"))
                {
                    descripcion.Text = fec + "   " + elemento.InnerText + "         "  +asist;
                }
                
            }      
            
        }
        public void eventHint()
        {
            asistentes.Text = navegador.Document.GetElementById("userNumber").InnerText;
            descripcion.Text = navegador.Document.GetElementById("main-info").InnerText;
        }
        public void zonaTuristica()
        {
            foreach (HtmlElement elemento in navegador.Document.All)
            {
                if (elemento.GetAttribute("itemprop").Contains("name"))
                {
                    nombre.Text = elemento.InnerText;
                }
                
                if (elemento.GetAttribute("classname").Contains("pure-g linea-arriba"))
                {
                    descripcion.Text = elemento.InnerText;
                }
            } 
        }
        public void Eventbrite()
        {
            string fec = "";
            foreach (HtmlElement elemento in navegador.Document.All)
            {
                if (elemento.GetAttribute("classname").Contains("listing-hero-title"))
                {
                    nombre.Text = elemento.InnerText;
                }
                if (elemento.GetAttribute("classname").Contains("event-details__data"))
                {
                    lugar.Text = elemento.InnerText;
                }
                if (elemento.GetAttribute("classname").Contains("clrfix"))
                {
                    fec = elemento.InnerText;
                }
                if (elemento.GetAttribute("classname").Contains("js-xd-read-more-contents l-mar-top-3"))
                {
                    descripcion.Text = fecha + "    " + elemento.InnerText;
                }
            }
        }
    }
}

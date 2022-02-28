using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace Eventos_administrador
{
    class ConexionSQL
    {
        public static SqlConnection Conectar()
        {
            SqlConnection conexion = new SqlConnection(
                "Data Source=.;Initial Catalog=EventosApp;Integrated Security=True");
            return conexion;
        }
    }
}

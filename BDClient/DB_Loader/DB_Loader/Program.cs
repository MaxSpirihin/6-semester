using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DB_Loader
{
    class Program
    {
        static void Main(string[] args)
        {
            DBContext DB = new DBContext();

            Exception ex;
            if (!DB.GeneratePeopleFromCompaniesExtra(out ex))
                Console.WriteLine(ex.Message);
            else
                Console.WriteLine("ItsDone");

            Console.ReadKey();
        }
    }
}

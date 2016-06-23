using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
 

namespace DB_Loader
{
    [Table("People")]
    public class People
    {
        [Key]
        public int Id { get; set; }

        public string Name { get; set; }

        public string BirthDay { get; set; }

        public string Position { get; set; }

        public int CompanyId { get; set; }

        public static People FromString(DBContext db,string str)
        {
            People result = new People();
            string[] parts = str.Split(';');

            if (parts.Count() < 4)
                return null;

            if (String.IsNullOrWhiteSpace(parts[1]))
                return null;

            result.Name = parts[1];
            result.BirthDay = parts[2];
            result.Position = parts[3];

            string compName = parts[4];

            if (compName.Length < 3)
                return null;

            Company comp = db.Companies.FirstOrDefault(c => c.Name.Contains(compName));
            
            if (comp == null) 
                return null;


            result.CompanyId = comp.Id;
            return result;
        }
    }
}

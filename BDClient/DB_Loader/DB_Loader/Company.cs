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
    [Table("Companies")]
    public class Company
    {
        [Key]
        public int Id { get; set; }

        public string Name { get; set; }

        public string INN { get; set; }

        public string ShortName { get; set; }

        public string OGRN { get; set; }

        public string LawAddress { get; set; }

        public string ActivityKind { get; set; }

        public string Address { get; set; }

        public string KPP { get; set; }

        public string Region { get; set; }

        public string Phone { get; set; }

        public string Email { get; set; }

        public string Site { get; set; }

        public string Extra { get; set; }


        public static Company FromString(string str)
        {
            Company result = new Company();
            string[] parts = str.Split('|');

            if (parts.Count() < 17)
                return null;
            
            result.Name = parts[0];
            result.INN = parts[1];
            result.ShortName = parts[2];
            result.OGRN = parts[3];
            result.LawAddress = parts[4];
            result.ActivityKind = parts[5];
            result.Address = parts[6];
            result.KPP = parts[7];
            result.Region = parts[9];
            result.Phone = String.IsNullOrWhiteSpace(parts[10]) ? parts[11] : parts[10];
            result.Email = parts[12];
            result.Site = parts[13];
            result.Extra = parts[16];
            return result;
        }
    }
}

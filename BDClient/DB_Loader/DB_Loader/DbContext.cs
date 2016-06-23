using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DB_Loader
{
    public class DBContext : System.Data.Entity.DbContext
    {
        public DBContext()
            :base("DbConnection")
        { }
          
        public DbSet<Company> Companies { get; set; }
        public DbSet<People> _People { get; set; }


        public bool AddCompaniesFromFile(string path,out Exception ex)
        {
            ex = null;

            try
            {
                string file = File.ReadAllText(path);
                string[] _comps = file.Split('\n');

                int percent = -1;
                for (int i = 0 ; i< _comps.Length; i++)
                {
                    Company company = Company.FromString(_comps[i]);

                    if (company != null)
                        Companies.Add(company);

                    if ((i*100)/_comps.Length != percent)
                    {
                        percent++;
                        SaveChanges();
                        Console.WriteLine(String.Format("{0}%", percent));
                    }
                }

                SaveChanges();
            }
            catch(Exception e)
            {
                ex = e;
            }

            return ex == null;
        }


        public bool AddPeopleFromFile(string path, out Exception ex)
        {
            ex = null;

            try
            {
                string file = File.ReadAllText(path);
                string[] _pl = file.Split('\n');

                int percent = -1;
                for (int i = 0; i < _pl.Length; i++)
                {
                    People people = People.FromString(this, _pl[i]);

                      if (people != null)
                          _People.Add(people);

                    if ((i * 1000) / _pl.Length != percent)
                    {
                        percent++;
                        SaveChanges();
                        Console.WriteLine(String.Format("{0}%", percent*0.1));
                    }
                }

                SaveChanges();
            }
            catch (Exception e)
            {
                ex = e;
            }

            return ex == null;
        }


        public bool GeneratePeopleFromCompaniesExtra(out Exception ex)
        {
            ex = null;

            try
            {
                string S1 = "Должность:";
                string S2 = "ФИО:";
                string S3 = "ИНН:";
                int Count = Companies.Count();
                int i = 0;
                int percent = -1;
                

                foreach (var c in Companies.Select(x => new { Id = x.Id, Extra = x.Extra }).ToList())
                {
                    i++;

                    if (c.Extra.IndexOf(S1) == -1)
                        continue;

                    int pos1 = c.Extra.IndexOf(S1) + S1.Length;
                    int pos2 = c.Extra.IndexOf(S2) + S2.Length;
                    int pos3 = c.Extra.IndexOf(S3);
                    string Position = c.Extra.Substring(pos1, pos2 - pos1 - S2.Length).Trim();
                    string Name = c.Extra.Substring(pos2, pos3 - pos2).Trim();

                    People p = new People()
                    {
                        CompanyId = c.Id,
                        Name = Name,
                        Position = Position
                    };

                    _People.Add(p);

                    if ((i * 1000) / Count != percent)
                    {
                        percent++;
                        SaveChanges();
                        Console.WriteLine(String.Format("{0}%", percent * 0.1));
                    }
                    
                }
            }
            catch (Exception e)
            {
                ex = e;
            }

            return ex == null;
        }
        
    }
}

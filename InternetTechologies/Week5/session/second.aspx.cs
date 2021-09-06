using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace sessionCookie
{
    public partial class second : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if ( !IsPostBack )
            {
                string r = Session["Roll"].ToString(); 
                string n = Session["Name"].ToString();
                string s = Session["Subject"].ToString() ;
                l1.Text = "Name - " + n + " Roll - " + r + " Subject - " + s;
                HttpCookie counter = new HttpCookie("Clicked");
                counter["Clicked"] = "1";
                counter.Expires.AddYears(1);
                Response.Cookies.Add(counter);
            }
        }
        protected void dispCookie ( object sender , EventArgs e )
        {
            string s = Request.Cookies["Clicked"].Value.ToString();
            int val; 
            int.TryParse(s, out val);
            val = val + 1;
            Response.Cookies["Clicked"].Value = val.ToString() ;
            l2.Text = "Clicked - " + val.ToString() + " times "; 
        }
    }
}
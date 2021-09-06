using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace sessionCookie
{
    public partial class first : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if ( !IsPostBack)
            {
                Subjects.Items.Add("History");
                Subjects.Items.Add("Geography");
                Subjects.Items.Add("Maths");
                Subjects.Items.Add("English");
            }
        }
        protected void GoNewPage ( object sender , EventArgs e)
        {
            Session["Subject"] = Subjects.SelectedItem.Text;
            Session["Name"] = Name.Text;
            Session["Roll"] = Roll.Text;
            Response.Redirect("second.aspx"); 
        }
    }
}
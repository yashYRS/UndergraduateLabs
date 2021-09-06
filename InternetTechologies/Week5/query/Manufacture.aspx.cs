using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace queryString
{
    public partial class Manufacture : System.Web.UI.Page
    {
        string []model = { "Toyota" , "Maruti" , "Honda" } ;
        string []names= { "Bharti Automobiles", "OSL Motors", "Axxela Motorworks" };
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack) {
                foreach( string s in model)
                {
                    ModelNames.Items.Add(s); 
                }
                
            }
        }
        protected void DisplayName(object sender, EventArgs e)
        {
            string temp = ModelNames.SelectedItem.Text;
            string temp2; 
            int idx = 0;
            
            foreach ( string s in model)
            {
                if (s == temp)
                    break;
                idx++; 
            }
            temp = HttpUtility.UrlEncode(temp);
            temp2 = HttpUtility.UrlEncode(names[idx]);
            Response.Redirect("Information.aspx?model=" + temp + "&name=" + temp2);
        }
    }
}
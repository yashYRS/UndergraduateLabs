using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace queryString
{
    public partial class Information : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                lblMod.Text = HttpUtility.UrlDecode(Request.QueryString["model"]);
                lblName.Text = HttpUtility.UrlDecode(Request.QueryString["name"]);
            }
        }
    }
}
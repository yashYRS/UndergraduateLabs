using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace ThemeBasic
{
    public partial class changeTheme : System.Web.UI.Page
    {
        static string themeValue;
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        public changeTheme()
        {
            this.PreInit += new EventHandler(Page_PreInit);
        }

        private void Page_PreInit(object sender, EventArgs e)
        {
            Page.Theme = themeValue;
        }

        protected void changeIt(object sender, EventArgs e)
        {
            themeValue = ListBox1.SelectedItem.Value;
            Response.Redirect(Request.Url.ToString());
        }
    }
}
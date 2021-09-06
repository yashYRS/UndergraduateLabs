using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace question2
{
    public partial class first : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void butClick(object sender, EventArgs e)
        {
            string temp = TakeInput.Text; 
            MainText.Text = temp ; 
        }
        protected void ChooseImg(object sender, EventArgs e)
        {
            Image1.ImageUrl = "~/images/" + ImageList.SelectedValue + ".jpg"; 
        }
        protected void ChooseBG(object sender, EventArgs e)
        {
            form1.Attributes["bgcolor"] = BGList.SelectedValue ;
        } 
        protected void ChooseFontSize(object sender, EventArgs e)
        {
            string temp = FontSize.SelectedValue;
            switch (temp)
            {
                case "Small":
                    MainText.Style["font-size"] = "8px"; 
                    break;
                case "Large":
                    MainText.Style["font-size"] = "11px";
                    break;
                case "Medium":
                    MainText.Style["font-size"] = "14px";
                    break;
                case "Huge":
                    MainText.Style["font-size"] = "17px";
                    break;
                default:
                    break;
            }
        }
    }
}
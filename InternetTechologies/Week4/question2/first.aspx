<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="first.aspx.cs" Inherits="question2.first" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body >
    <form id="form1" runat="server">
        <div>
            
        <asp:Panel ID= "Panel1"  runat = "server" HorizontalAlign="Center">
            <asp:Image ID="Image1" runat="server" ImageUrl="~/images/cat.jpg" />
            <br /><br />
             <asp:Label ID="MainText" runat="server" align="center" Text=""></asp:Label>
        </asp:Panel>
            <asp:DropDownList ID="ImageList" runat="server" AutoPostBack="True"  OnSelectedIndexChanged="ChooseImg"> 
                    <asp:ListItem>dog</asp:ListItem> 
                    <asp:ListItem>cat</asp:ListItem> 
                    <asp:ListItem>lion</asp:ListItem> 
                    <asp:ListItem>tiger</asp:ListItem> 
            </asp:DropDownList>
            <asp:DropDownList ID="BGList" runat="server" AutoPostBack="True"  OnSelectedIndexChanged="ChooseBG"> 
                    <asp:ListItem>red</asp:ListItem> 
                    <asp:ListItem>blue</asp:ListItem> 
                    <asp:ListItem>magenta</asp:ListItem> 
                    <asp:ListItem>green</asp:ListItem> 
            </asp:DropDownList>
            <asp:DropDownList ID="FontSize" runat="server" AutoPostBack="True"  OnSelectedIndexChanged="ChooseFontSize"> 
                    <asp:ListItem>Small</asp:ListItem> 
                    <asp:ListItem>Medium</asp:ListItem> 
                    <asp:ListItem>Large</asp:ListItem> 
                    <asp:ListItem>Huge</asp:ListItem> 
            </asp:DropDownList> 
            <asp:TextBox ID="TakeInput" runat="server"> Enter the Text for the magazine here </asp:TextBox>
            <asp:Button OnClick="butClick" runat="server" Text="Click"/>
        </div>
    </form>
</body>
</html>

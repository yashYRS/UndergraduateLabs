<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="changeTheme.aspx.cs" Inherits="ThemeBasic.changeTheme" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
           <h3>Select your page Theme : </h3>
                <asp:ListBox ID="ListBox1" runat="server" AutoPostBack="True" Height="41px" onselectedindexchanged= "changeIt" Width="175px">
                <asp:ListItem>Summer</asp:ListItem>
                <asp:ListItem>Monsoon</asp:ListItem>
            </asp:ListBox>
            <br />
        </div>
    </form>
</body>
</html>

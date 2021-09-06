<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="first.aspx.cs" Inherits="sessionCookie.first" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            Enter Roll - <asp:TextBox ID="Roll" runat="server"></asp:TextBox>
            <br />
            Enter Name - <asp:TextBox ID="Name" runat="server"></asp:TextBox>
            <br />
            Subjects - <asp:DropDownList ID="Subjects" runat="server"></asp:DropDownList>
            <br />
            <asp:Button ID="submit" Text="Submit" runat="server" OnClick="GoNewPage" />
        </div>
    </form>
</body>
</html>

<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="second.aspx.cs" Inherits="sessionCookie.second" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Label id="l1" Text="" runat="server"></asp:Label>
            <br />
            <asp:Label id="l2" Text="" runat="server"></asp:Label>
            <br />
            <asp:Button ID="fb" runat="server" Text="Show Counter" OnClick="dispCookie" />
        </div>
    </form>
</body>
</html>

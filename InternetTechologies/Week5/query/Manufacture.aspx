<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Manufacture.aspx.cs" Inherits="queryString.Manufacture" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <asp:DropDownList ID="ModelNames" runat="server" AutoPostBack="true" OnSelectedIndexChanged="DisplayName">
        </asp:DropDownList>
        <div>
        </div>
    </form>
</body>
</html>

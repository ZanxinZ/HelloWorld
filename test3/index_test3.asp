<html>
<body>
<%
	
	If request.cookies("c_name")<>""Then 
	Response.Write "<a href='test3.asp?jr=1'>������ҳ</a>"
	Else 
	Response.redirect "login.asp"
	End if
%>
</body>
</html>
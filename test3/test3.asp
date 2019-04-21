<html>
	<head>
	<meta http-equiv="Content-Type" content="test/html";charset=gb2312>
	<title>默认选项</title>
	</head>
	<body>
	<%
		Dim lb,user_name
		user_name=request.Cookies("c_name")
		lb=request.QueryString("jr")
		If lb="0" Then
			Response.Write "欢迎"&user_name&"加入我们"
		Else  
			Response.Write "欢迎"&user_name&"回来"
		End If 
	%>
	</body>
</html>
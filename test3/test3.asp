<html>
	<head>
	<meta http-equiv="Content-Type" content="test/html";charset=gb2312>
	<title>Ĭ��ѡ��</title>
	</head>
	<body>
	<%
		Dim lb,user_name
		user_name=request.Cookies("c_name")
		lb=request.QueryString("jr")
		If lb="0" Then
			Response.Write "��ӭ"&user_name&"��������"
		Else  
			Response.Write "��ӭ"&user_name&"����"
		End If 
	%>
	</body>
</html>
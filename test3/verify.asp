<html>
	<body>
	<%
		
		Dim error_message
		error_message=""
		If Trim(Request("user_name"))="" Then
		error_message=error_message&"请填写您的用户名<br>"
		End If 
		If Trim(Request("user_pass1"))=""Or Len(Trim(Request("user_pass1")))<6 Then
		error_message=error_message&"密码不能为空且不能少于6位数！<br>"
		End If
		If Trim(Request("user_pass1"))<>Trim(Request("user_pass2")) Then
		error_message=error_message&"<br>您两次输入密码不相同，请重新输入<br>"
		End If
		If instr(Request("user_email"),"@")=0 Then
		error_message=error_message&"请输入有效合法的E-maile地址<br>"
		End If
		If Request("user_qq")=""And isNumeric("use_qq")=False Then
		error_message=error_message&"QQ号码应当是数字，请重新输入<br>"
		End If
		If error_message <> "" Then
		Response.write error_message&"<p>请<a href='login.asp'>返回</a>重新输入！<br>"
		Else 
		Response.cookies("c_name")=Trim(Request("user_name"))
		Response.cookies("c_name").expires=Date()+3*365
		Response.write "<a href='test3.asp?jr=0'>您通过了验证</a><br>点击进入主页<br>"
		End If 
	%>
	</body>
</html>
<html>
	<body>
	<%
		
		Dim error_message
		error_message=""
		If Trim(Request("user_name"))="" Then
		error_message=error_message&"����д�����û���<br>"
		End If 
		If Trim(Request("user_pass1"))=""Or Len(Trim(Request("user_pass1")))<6 Then
		error_message=error_message&"���벻��Ϊ���Ҳ�������6λ����<br>"
		End If
		If Trim(Request("user_pass1"))<>Trim(Request("user_pass2")) Then
		error_message=error_message&"<br>�������������벻��ͬ������������<br>"
		End If
		If instr(Request("user_email"),"@")=0 Then
		error_message=error_message&"��������Ч�Ϸ���E-maile��ַ<br>"
		End If
		If Request("user_qq")=""And isNumeric("use_qq")=False Then
		error_message=error_message&"QQ����Ӧ�������֣�����������<br>"
		End If
		If error_message <> "" Then
		Response.write error_message&"<p>��<a href='login.asp'>����</a>�������룡<br>"
		Else 
		Response.cookies("c_name")=Trim(Request("user_name"))
		Response.cookies("c_name").expires=Date()+3*365
		Response.write "<a href='test3.asp?jr=0'>��ͨ������֤</a><br>���������ҳ<br>"
		End If 
	%>
	</body>
</html>
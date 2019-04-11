<% Option Explicit								'放在程序首行，强制变量声明  %>
<html>
<body>
	<%
	Dim temp,length,count,strA,I
	count=0
	temp="VBScript*is*good!"
	Length=Len(temp) 
	strA = Split(temp, "*")		'以*为分界符拆分
	For I=1 To Length
		If Mid(temp,I,1)="*" Then 
			count=count+1
		End If
	Next 
	Response.Write "* count="&count&"<P>"
	Response.Write strA(0) & "<P>"
	Response.Write strA(1) & "<P>"
	Response.Write strA(2) & "<P>"
	%>
</body> 
</html> 

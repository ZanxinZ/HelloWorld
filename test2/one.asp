<html>
<head>
	<title>简单的日历</title>
</head>
<body>
	<h2 align="center"><%=Year(Date())%>年 <%=Month(Date())%>月 <%=Day(Date())%>日 <%
	If Weekday(Date())=1 Then
	Response.write "星期日"
	ElseIf  Weekday(Date())=2 Then
	Response.write "星期一"
	ElseIf  Weekday(Date())=3 Then
	Response.write "星期二"
	ElseIf  Weekday(Date())=4 Then
	Response.write "星期三"
	ElseIf  Weekday(Date())=5 Then
	Response.write "星期四"
	ElseIf  Weekday(Date())=6 Then
	Response.write "星期五"
	ElseIf  Weekday(Date())=7 Then
	Response.write "星期六"
	End If
	%>
	</h2>
	<h3 align="center"><%=Year(Date())%>年<%=Month(Date())%>月</h3>
	<table border="1" align=center>
		<tr align=night>
			<td>日</td><td>一</td><td>二</td><td>三</td><td>四</td><td>五</td>
			<td>六</td>
		</tr>
		<%  
			
			theDate=arrayDate()
			
			Dim I,J
			
			
		For I=1 To 6
			Response.write "<tr>"
			For J=1 To 7
			If theDate(I,J)<>0 Then
				If theDate(I,J)=Day(Date()) Then
					Response.write "<td><font color=blue><b>"&theDate(I,J)&"</b></font></td>"
				ElseIf J=7 Or J=1 Then
					Response.write "<td><font color=red>"&theDate(I,J)&"</font></td>"
				Else 
					Response.write "<td>"&theDate(I,J)&"</td>"
				End If
				
			ElseIf I=1 Then
						Response.write "<td>"&"</td>"
			ElseIf I=5 Then
						Response.write "<td>"&"</td>"
					
					
			End If
			Next
			Response.write "</tr>"
		Next	
		%>
	</table>
	<h3 align="center">
	<%
	If Day(Date())=25 Then
	Response.write "请注意，明天可能有病毒发作"
	End If
	%>
	</h3>
	<%
	Function numday()
	Dim IntDay,I
	intday=28
	For I=29 To 31
	If IsDate(Year(Date())&"-"&Month(Date())&"-"&I)Then
		intDay=I
		End If
	Next
	numDay=intDay
	End Function
	
	Function firstDay()
	firstDay=WeekDay(Year(Date())&"-"&Month(Date())&"-1")
	End Function
	
	
	Function arrayDate()
	Dim J,K,I,arrayTemp(6,7)

	
	For I=1 To 6 
		For J=1 To 7
			arrayTemp(I,J)=0
		Next
	Next
	For K=1 To numday()
		I=(K+firstDay()-2)\7+1
		J=(K+firstDay()-1)Mod 7
		If j=0 Then J=7
		arrayTemp(I,J)=K
		Next
		arrayDate=arrayTemp
	End Function
	Function numRow()
	numRow()=(numDay()+firstDay()-2)\7+1
	End Function
	%>
</body>
</html>

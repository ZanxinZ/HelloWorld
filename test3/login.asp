<html>
<head>
	<title>用户注册</title>
	<meta http-equiv="Content-Type" content="test/html";charset=gb2312>
</head>
<body>
	<h2 align="center">用户注册</h2>
	<form method="POST" action="verify.asp" name="myform">
	<table border="0" align="center">
	<tr><td>用户名:</td><td><input type="test" name="user_name" size="20"></td></tr>
	<tr><td>密码：</td><td><input type="test" name="user_pass1" size="20">*(码长度不能小于6)</td></tr>
	<tr><td>密码确认:</td><td><input type="test" name="user_pass2" size="20"></td></tr>
	<tr><td>Email:</td><td><input type="test" name="user_email" size="20"></td></tr>
	<tr><td>QQ:</td><td><input type="test" name="user_qq" size="20"></td></tr>
	<tr><td colspan="2"><p align="center"><input type="submit" value="提交" name="B1">&nbsp;&nbsp;<input type="reset" value="重置" name="B2"></td></tr>
	</table>
	</form>
</body>
</html>
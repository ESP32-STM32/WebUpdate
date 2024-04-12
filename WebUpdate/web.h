const char Web_page[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<style>
.displayobject{
background-color:#00FF00;
color:black;
padding:20px;
	font-family: sans-serif;
	margin: auto;
	text-align: center;
}
h1 {
  font-size: 100px;
  color: BLACK;
}
</style>
	<style>
.btn {
-webkit-appearance: none;
width: 400px;
height: 200px;
font-size: 80px;
display: flex;
align-items: center;
justify-content: center;
padding: 6px 12px;
cursor: pointer;
background-color: #f8f8f8;
border: 1px solid #ccc;
border-radius: 4px;
margin: 0px 20px 0px 20px;
}
.btn:hover {
  background-color:#78DBE2;
  transition: 0.7s;
}
.btn[disabled=true] {
background-color: #cccccc;
color:gray;
cursor: no-drop;
}
</style>
	<body>
		<div class="displayobject">
			<h1>Обновление прошивки</h1>
			<br>
				<form method='POST' action='/update' enctype='multipart/form-data'>
					<div style="display:flex; justify-content:center; align-items:center;">
						<input type='file' name='update' id="file-upload" style="display: none;">
							<label for="file-upload" class="btn">Выбрать файл</label>
							<input type='submit' id='label0' style="display: none;" value='Update'>
								<label for='label0' id='label1' class='btn'>Загрузить</label>
							</div>
						</form>
					</div>
				</body>
			</html>
)=====";
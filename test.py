#!/usr/bin/python3
import os

print("Content-Type: text/html; charset=utf-8")
print()
print('''\
<!DOCTYPE html>
<meta charset="utf-8" />
<a href="./">Up</a>
<p>Upload files</p>
<form action="test.py" method="POST" enctype="multipart/form-data">
	<input type="file" name="myFile1">
    <br>
    <br>
	<input type="file" name="myFile2">
    <br>
    <br>
	<input type="submit" value="Upload">
</form>
''')
print(os.getenv('HTTP_USER_AGENT'))
print('<br>')
print("REQUEST_METHOD: ",os.environ.get('REQUEST_METHOD'))
print('<br>')
print("QUERY_STRING: ", os.environ.get('QUERY_STRING'))
print('<br>')
print(os.environ.get('HTTP_CONTENT_LENGTH'))
print('<br>')
print(os.environ.get('CONTENT_TYPE'))
print('<br>')
contents = []
while True:
    try:
        line = input("")

    except EOFError:
        break
    contents.append(line)
print('content: <br>')
for i in contents:
    print(i+'<br>')
    # if()

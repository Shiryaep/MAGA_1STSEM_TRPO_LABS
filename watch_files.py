#!/usr/bin/python3
import os
print("Content-Type: text/html; charset=utf-8\r\n\r\n")
print("<style>h4{ font-family: \"Segoe UI\";} </style>")
print()
print("<head><title>File Watch</title><link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\"></head>")
print("<a href=\"./\"><button class=\"button-back\">Наверх</button></a><br>")
# exit()
FILESPATH = './usrfiles'
os.chdir(FILESPATH)
files = [f for f in os.listdir('.') if os.path.isfile(f)]
if os.getenv("REQUEST_METHOD").lower() == 'post':
    file = input().split('=')[1]
    print("DELETE FILE: ", file)
    if file in files:
        os.remove(file)

files = [f for f in os.listdir('.') if os.path.isfile(f)]
if files == []:
    print("<h4>folder is empty:(</h4>")

for file in files:
    print("<h4>filename:",file,"</h4>")
    print(f'''
    <form action="watch_files.py" id="Form" enctype="application/x-www-form-urlencoded" method="post">
        <input id="keyinpgetall" name="delete" value="{file}" hidden="hidden">
        <input class=\"button-delete\" type="submit" value="Delete this file">
    </form>
    ''')
    with(open(file,"r",encoding='utf8')) as f:
        contents = []
        while line := f.readline():
            for i in [["\"","\\&quot;"], ["<","&lt;"], [">","&gt;"]]:
                line = str(line).replace(i[0],i[1])
            print(line+'</br>')

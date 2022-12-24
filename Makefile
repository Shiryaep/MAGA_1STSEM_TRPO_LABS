.PHONY: all
all: db test files
db:
	g++ db.cpp HTTP.cpp working_with_db.cpp  -o db.cgi
test:
	g++ HTTP.cpp cgi_handler.cpp -o test.cgi
files:
	g++ db.cpp HTTP.cpp working_with_files.cpp -o uploadFile.cgi
session:
	g++ HTTP_session.cpp working_with_session.cpp HTTP.cpp -l tacopie -l cpp_redis -o session.cgi
clean:
	rm *.cgi
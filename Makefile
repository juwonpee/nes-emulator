build:
	echo: "Building"
	g++ src/main.cpp `wx-config --cxxflags --libs std` -o build/build.out

clean:
	rm build/*
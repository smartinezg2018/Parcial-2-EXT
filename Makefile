# Nombre del ejecutable
TARGET = programa

# Archivos fuente
SOURCES = main.cpp Graph.cpp

# Compilador
CXX = g++


# Regla principal: compilar el programa
$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(TARGET)
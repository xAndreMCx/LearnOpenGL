EXE = Application.exe

SRC_PATH = ./src
LIBRARIES_PATH = ../libraries
TESTS_PATH = $(SRC_PATH)/tests
VENDOR_PATH = $(SRC_PATH)/vendor
IMGUI_PATH = $(VENDOR_PATH)/imgui
GLAD_FILE_PATH = $(VENDOR_PATH)/glad
GLM_PATH =$(VENDOR_PATH)/glm
STB_IMAGE_PATH = $(VENDOR_PATH)/stb_image
GLAD_PATH = $(LIBRARIES_PATH)/GLAD/include
GLFW_PATH = $(LIBRARIES_PATH)/GLFW/include

MY_SOURCES = $(SRC_PATH)/Application.cpp $(SRC_PATH)/VertexArray.cpp $(SRC_PATH)/VertexBuffer.cpp $(SRC_PATH)/VertexBufferLayout.cpp
MY_SOURCES += $(SRC_PATH)/IndexBuffer.cpp $(SRC_PATH)/Shader.cpp $(SRC_PATH)/Texture.cpp $(SRC_PATH)/Renderer.cpp $(SRC_PATH)/Window.cpp
MY_SOURCES += $(SRC_PATH)/Camera.cpp
MY_SOURCES += $(TESTS_PATH)/Test.cpp $(TESTS_PATH)/ClearColor.cpp $(TESTS_PATH)/Triangle.cpp $(TESTS_PATH)/TextureTest.cpp
MY_SOURCES += $(TESTS_PATH)/ZeldaLogo.cpp $(TESTS_PATH)/Transformations.cpp $(TESTS_PATH)/LightingColors.cpp 
MY_SOURCES += $(TESTS_PATH)/CameraTest.cpp $(TESTS_PATH)/LightingApp.cpp 

LIBS_SOURCES = $(VENDOR_PATH)/glad.c $(VENDOR_PATH)/stb_image/stb_image.cpp
LIBS_SOURCES += $(IMGUI_PATH)/imgui.cpp $(IMGUI_PATH)/imgui_impl_opengl3.cpp $(IMGUI_PATH)/imgui_impl_glfw.cpp
LIBS_SOURCES += $(IMGUI_PATH)/imgui_draw.cpp $(IMGUI_PATH)/imgui_tables.cpp $(IMGUI_PATH)/imgui_widgets.cpp

SOURCES = $(LIBS_SOURCES) $(MY_SOURCES)

MY_OBJS = $(addprefix obj/, $(addsuffix .o,$(basename $(notdir $(MY_SOURCES)))))
LIBS_OBJS = $(addprefix obj/, $(addsuffix .o,$(basename $(notdir $(LIBS_SOURCES)))))
OBJS = $(LIBS_OBJS) $(MY_OBJS)


CXX = g++
CXXFLAGS = -I$(VENDOR_PATH) -I$(GLAD_PATH) -I$(GLFW_PATH) -I$(SRC_PATH)
CXXFLAGS += -g -Wall
LIBS = -L$(LIBRARIES_PATH)/GLFW/lib -lglfw3 -lopengl32 -lgdi32


EXEC_VENDOR = $(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: $(GLAD_FILE_PATH)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: $(IMGUI_PATH)/%.cpp
	$(EXEC_VENDOR)

obj/%.o: $(GLM_PATH)/%.cpp
	$(EXEC_VENDOR)

obj/%.o: $(STB_IMAGE_PATH)/%.cpp
	$(EXEC_VENDOR)

obj/%.o: $(TESTS_PATH)/%.cpp
	$(EXEC_VENDOR) 

all: $(EXE)
	@echo Build complete

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

remake: clean_all all
	
clean:
	rm -f $(EXE) $(MY_OBJS)

clean_libs: 
	rm -f $(LIBS_OBJS)

clean_all: clean clean_libs
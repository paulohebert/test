TARGET = aedes-attack

BUILD_DIR = build

EMCC = em++

EMFLAGS = -O2\
		  -Iinclude\
		  -sLEGACY_GL_EMULATION\
		  -sUSE_WEBGL2=1\
		  --shell-file shell.html\
		  -sALLOW_MEMORY_GROWTH\
		  -DMA_ENABLE_AUDIO_WORKLETS\
		  -sAUDIO_WORKLET=1\
		  -sWASM_WORKERS=1\
		  -sASYNCIFY\
		  --preload-file assets@../assets

SRC_FILES := $(wildcard src/*.cpp)

all: wasm

wasm: $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)
	$(EMCC) $(SRC_FILES) $(EMFLAGS) -o $(BUILD_DIR)/$(TARGET).html

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean wasm
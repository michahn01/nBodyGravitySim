build_web_assembly:
	emcc -o output.html \
	    ../src/simulation.cpp ../src/utility/InputHandler.cpp \
	    ../src/utility/TextureHandler.cpp ../src/utility/QuadTree.cpp \
		../src/ProgramObjects/Object.cpp \
	    ../src/ProgramObjects/Mass.cpp ../src/ProgramObjects/buttons/DropDownButton.cpp \
	    ../src/ProgramObjects/buttons/DropDown.cpp ../src/ProgramObjects/buttons/Button.cpp \
		../src/ProgramObjects/MassPlacer.cpp ../src/ProgramObjects/buttons/MassPlaceDropDown.cpp\
	    -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -pthread --use-preload-plugins \
	    --preload-file ../resources@resources

run_web_assembly:
	emrun output.html

run:
	emrun index.html
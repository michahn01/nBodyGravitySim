build_web_assembly:
	emcc -o output.html \
	    test.cpp utility/InputHandler.cpp \
	    utility/TextureHandler.cpp utility/QuadTree.cpp \
	    ProgramObjects/Mass.cpp ProgramObjects/buttons/ExampleConfigsButton.cpp \
	    ProgramObjects/buttons/DropDown.cpp ProgramObjects/buttons/Button.cpp \
	    -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -pthread --use-preload-plugins \
	    --preload-file resources/textures/euler_3_body.png \
	    --preload-file resources/textures/example_configs_buttons.png \
	    --preload-file resources/textures/pause_button.png \
	    --preload-file resources/textures/reset_button.png \
	    --preload-file resources/textures/resume_button.png \
	    --preload-file resources/textures/start_simulation_button.png \
	    --preload-file resources/textures/unstable_3_body.png \
	    --preload-file resources/textures/white_mass.png \
	    --preload-file resources/mass_configurations/euler_3_body.csv \
	    --preload-file resources/mass_configurations/sample_four_body.csv \
	    --preload-file resources/mass_configurations/unstable_3_body.csv

run_web_assembly:
	emrun output.html

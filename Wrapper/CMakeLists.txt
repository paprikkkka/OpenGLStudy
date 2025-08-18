# CMakeLists.txt for the App module
# Add all cpp files in the current directory to the app library
file(GLOB_RECURSE WRAPPER ./ *.cpp)

# ƒtƒHƒ‹ƒ_“à‚·‚×‚Ä‚Ìcpp‚ðlib‚É’Ç‰Á
add_library(wrapper ${WRAPPER})
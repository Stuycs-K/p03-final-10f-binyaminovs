# Dev Log:

## Solomon Binyaminov

### January 6:
- Finalized project proposal and README
- Set up Makefile with proper ncurses linking and compiler flags
- Initial experiments with ncurses input/output
Total ~1 hour with ncurses experimentation

### January 7-9:
No work done

### January 10-13:
Sick. Sorry about not being in class last day as I was supposed to give in sick note (I have a PSAL meet). I'll hhave my mom email or something similar to confirm

### January 14:
- Created editor skeleton
- Initialized ncurses and clean shutdown behavior
- Enabled raw input and disabled echo
- Implemented main input loop and exit functionality
- Switched to switch/case input handling
- Added keycode printing for debugging
- Introduced editor state struct for cursor and screen data
- Implemented cursor movement
- Added screen size tracking and resize handling
- Prevented cursor from leaving screen bounds
- Implemented basic line storage and helper functions
- Rendered text lines to the screen
- Fixed Makefile warnings
Total ~3 hours

### January 15
- Added file opening and basic file handling
- Implemented character insertion and rendering
- Added backspace support
- Implemented newline insertion and fixed Enter key bugs
- Added file saving functionality
- Implemented status bar with file info and cursor position
- Added line deletion (Ctrl+D)
- Added text search (Ctrl+F)
- Fixed cursor visibility and major input bugs
Total ~3 hours

### January 16
- Demo Video
- Documentation
- Main bug fixes, polishing up
- Going through code again
- Renamed main source file to edit.c
Total ~1 hour

# Where to save the file
Output demo.gif

# Visual Settings
Set FontSize 22
Set Width 1200
Set Height 600
Set Theme "Catppuccin Frappe" # Use a nice theme
Set Padding 40
Set TypingSpeed 75ms

# Start the shell
Type "./mini-shell" Enter
Sleep 1s

# 1. Show off directory navigation
Type "pwd" Sleep 500ms Enter
Sleep 1.5s
Type "cd src" Sleep 500ms Enter
Sleep 1s
Type "pwd" Sleep 500ms Enter
Sleep 1.5s

# 2. Show off basic piping
Type "ls | grep .c" Sleep 500ms Enter
Sleep 2s

# 3. Show off a triple pipeline (the "power user" move)
Type "ls | grep .c | wc -l" Sleep 500ms Enter
Sleep 2s

# 4. Show off an error (to prove your shell handles them!)
Type "ls non_existent_file" Sleep 500ms Enter
Sleep 1.5s

# 5. Exit gracefully
Type "exit" Sleep 500ms Enter
Sleep 1s